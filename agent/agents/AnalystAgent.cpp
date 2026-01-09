//
// Created by Darian Sandru on 09.01.2026.
//

#include "AnalystAgent.h"

namespace {
    std::string normalize(std::string s) {
        Algorithm::toLower(s);
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());

        std::string out;
        bool prevSpace = false;
        for (char c : s) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!prevSpace) out += ' ';
                prevSpace = true;
            }
            else {
                out += c;
                prevSpace = false;
            }
        }
        return out;
    }

    std::vector<std::string> normalizeList(const std::vector<std::string>& input) {
        std::vector<std::string> out;
        out.reserve(input.size());
        for (auto s : input)
            out.push_back(normalize(std::move(s)));
        return out;
    }
}

void AnalystAgent::start(const std::string& message) {
    OutputDevice::writeNewLine("Analyst Agent, with ID: " + std::to_string(AgentMetaData::ANALYST_AGENT_ID) + ", speaking:");
    std::vector<std::string> parts = Algorithm::split(message, ':');
    if (parts.size() != 8) {
        sendResponse("Invalid request format.", AgentMetaData::USER_AGENT_ID);
        return;
    }

    if (!parts[0].empty() && normalize(parts[1]) == "end") {
        std::vector<std::string> songs = normalizeList(Algorithm::split(parts[0], ','));
        std::string messageString = "play:";
        for (const std::string& song : songs)
            messageString += song + ",";
        if (!songs.empty()) messageString.pop_back();
        sendInfo(messageString);
        return;
    }

    std::vector<std::string> songs;
    if (normalize(parts[0]) != "na") {
        auto rawSongs = normalizeList(Algorithm::split(parts[0], ','));
        for (const auto& s : rawSongs)
            if (!s.empty())
                songs.push_back(s);
    }

    std::string album = normalize(parts[1]);
    std::string artist = normalize(parts[2]);
    std::string genre = normalize(parts[3]);
    std::string language = normalize(parts[7]);

    if (analyse(songs, album, artist, genre, language)) sendInfo(message);
}

void AnalystAgent::sendInfo(const std::string& message) {
    OutputDevice::writeNewLine("Analysis completed successfully!\n");
    if (message.rfind("play", 0) == 0) {
        Message msg(AgentMetaData::ANALYST_AGENT_ID, INFO, message);
        MessageBus::send(AgentMetaData::MUSIC_AGENT_ID, msg);
        return;
    }
    Message msg(AgentMetaData::ANALYST_AGENT_ID, INFO, message);
    MessageBus::send(AgentMetaData::MUSIC_PICKER_AGENT_ID, msg);
}

void AnalystAgent::sendResponse(const std::string& message, const size_t& receiver) {
    Message msg(AgentMetaData::ANALYST_AGENT_ID, RESPONSE, message);
    MessageBus::send(receiver, msg);
}

void AnalystAgent::run() {
    while (running) {
        auto messages = MessageBus::collect(agentID);
        while (!messages.empty()) {
            auto message = messages.front();
            messages.pop();
            if (message.type == INFO)
                start(message.message);
        }
    }
}

bool AnalystAgent::analyse(const std::vector<std::string>& songs, const std::string& album,
                           const std::string& artist, const std::string& genre, const std::string& language) {

    Ontology* ontology = OntologyFactory::getOntology("song");
    auto instances = OntologyFactory::getOntologyInstances(ontology);
    std::unordered_set<std::string> remainingSongs(songs.begin(), songs.end());

    bool albumExists = (album == "na");
    bool artistExists = (artist == "na");
    bool genreExists = (genre == "na");
    bool languageExists = (language == "na");

    for (const OntologyInstance* instance : instances) {
        const std::string name = normalize(instance->getValue("name").getTEXT());
        const std::string alb = normalize(instance->getValue("album").getTEXT());
        const std::string art = normalize(instance->getValue("artist").getTEXT());
        const std::string gen = normalize(instance->getValue("genre").getTEXT());
        const std::string lang = normalize(instance->getValue("language").getTEXT());

        remainingSongs.erase(name);

        if (!albumExists && alb == album) albumExists = true;
        if (!artistExists && art == artist) artistExists = true;
        if (!genreExists && gen == genre) genreExists = true;
        if (!languageExists && lang == language) languageExists = true;
    }

    bool valid = true;
    std::string errorMessage;

    if (!remainingSongs.empty()) {
        errorMessage += "Following songs do not exist: ";
        for (const auto& song : remainingSongs)
            errorMessage += song + ", ";
        errorMessage.erase(errorMessage.size() - 2);
        errorMessage += "\n";
        valid = false;
    }
    if (!albumExists) {
        errorMessage += "Album '" + album + "' does not exist!\n";
        valid = false;
    }
    if (!artistExists) {
        errorMessage += "Artist '" + artist + "' does not exist!\n";
        valid = false;
    }
    if (!genreExists) {
        errorMessage += "Genre '" + genre + "' does not exist!\n";
        valid = false;
    }
    if (!languageExists) {
        errorMessage += "Language '" + language + "' does not exist!\n";
        valid = false;
    }
    if (!valid) sendResponse(errorMessage, AgentMetaData::USER_AGENT_ID);
    return valid;
}