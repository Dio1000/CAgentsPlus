//
// Created by Darian Sandru on 07.01.2026.
//

#include "MusicPickerAgent.h"

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
}

void MusicPickerAgent::setup(const std::string& message) {
    std::vector<std::string> parts = Algorithm::split(message, ':');
    if (parts.size() != 8) return;

    if (parts[0] != "na") {
        auto rawSongs = Algorithm::split(parts[0], ',');
        for (const auto& s : rawSongs)
            if (!s.empty())
                availableSongs.push_back(s);
    }

    std::string album = parts[1];
    std::string artist = parts[2];
    std::string genre = parts[3];
    bool careRating = (parts[4] == "1");
    bool shorterLength = (parts[5] == "1");
    bool newerSong = (parts[6] == "1");
    std::string language = parts[7];

    if (album == "NA") ruleDecision->removeRuleByName("album");
    else ruleDecision->getRuleByName("album")->setField("album", Value(TEXT, album));
    
    if (artist == "NA") ruleDecision->removeRuleByName("artist");
    else ruleDecision->getRuleByName("artist")->setField("artist", Value(TEXT, artist));

    if (genre == "NA") ruleDecision->removeRuleByName("genre");
    else ruleDecision->getRuleByName("genre")->setField("genre", Value(TEXT, genre));

    if (!careRating) weightedDecision->removeWeight("rating");
    if (!shorterLength) weightedDecision->removeWeight("length");
    if (!newerSong) weightedDecision->removeWeight("release_date");

    if (language == "NA") ruleDecision->removeRuleByName("language");
    else ruleDecision->getRuleByName("language")->setField("language", Value(TEXT, language));
}

void MusicPickerAgent::pickMusic(const std::string& message) {
    OutputDevice::writeNewLine("Music Picker Agent, with ID: " + std::to_string(AgentMetaData::MUSIC_PICKER_AGENT_ID) + ", speaking:");
    OutputDevice::writeNewLine("Picking music...");

    Ontology* ontology = OntologyFactory::getOntology("song");
    std::vector<OntologyInstance*> instances = OntologyFactory::getOntologyInstances(ontology);
    std::unordered_map<double, std::vector<OntologyInstance*>> scoreInstanceMap;
    std::vector<double> scores;
    setup(message);

    for (OntologyInstance* instance : instances) {
        const std::string name = normalize(instance->getValue("name").getTEXT());
        if (!availableSongs.empty()) {
            if (std::find(availableSongs.begin(), availableSongs.end(), name) == availableSongs.end())
                continue;
        }

        double score = ruleDecision->getScore(instance) + weightedDecision->getWeight(instance);
        scoreInstanceMap[score].emplace_back(instance);
        scores.emplace_back(score);
    }

    std::sort(scores.begin(), scores.end());
    scores.erase(std::unique(scores.begin(), scores.end()), scores.end());
    std::reverse(scores.begin(), scores.end());

    std::queue<OntologyInstance*> songQueue;
    for (const double& score : scores) {
        for (OntologyInstance* instance : scoreInstanceMap[score]) {
            songQueue.push(instance);
        }
    }

    std::vector<OntologyInstance*> topSongs;
    size_t count = 0;
    OutputDevice::writeNewLine("Here are the top " + std::to_string(std::min(size_t(5), songQueue.size())) + " songs:");
    std::queue<OntologyInstance*> tempQueue = songQueue;

    while (!tempQueue.empty() && count < 5) {
        OntologyInstance* instance = tempQueue.front();
        tempQueue.pop();
        topSongs.push_back(instance);
        OutputDevice::writeNewLine(std::to_string(count + 1) + ". " + instance->getValue("name").getTEXT());
        count++;
    }

    while (true) {
        OutputDevice::writeNewLine("Please input your preferred order using the numbers, separated by commas:");
        std::string orderInput = normalize(InputDevice::readLineFromKeyboard());
        std::vector<std::string> orderParts;
        std::vector<std::string> finalQueue;

        if (orderInput.empty()) {
            for (const auto* song : topSongs) finalQueue.push_back(song->getValue("name").getTEXT());
        }
        else {
            orderParts = Algorithm::split(orderInput, ',');
            bool valid = true;
            for (const std::string& part : orderParts) {
                try {
                    int index = std::stoi(part) - 1;
                    if (index < 0 || static_cast<size_t>(index) >= topSongs.size()) {
                        valid = false;
                        break;
                    }
                    finalQueue.push_back(topSongs[index]->getValue("name").getTEXT());
                }
                catch (...) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                OutputDevice::writeNewLine("Invalid order. Please try again.");
                continue;
            }
        }

        std::string finalQueueString;
        for (size_t i = 0; i < finalQueue.size(); i++) {
            finalQueueString += finalQueue[i];
            if (i != finalQueue.size() - 1)
                finalQueueString += ",";
        }

        sendInfo(finalQueueString);
        break;
    }
}

void MusicPickerAgent::sendInfo(const std::string &message) {
    Message msg = Message(AgentMetaData::MUSIC_PICKER_AGENT_ID, INFO, message);
    MessageBus::send(AgentMetaData::MUSIC_AGENT_ID, msg);
}

void MusicPickerAgent::run() {
    while (running) {
        auto messages = MessageBus::collect(agentID);
        while (!messages.empty()) {
            auto message = messages.front();
            messages.pop();

            if (message.type == INFO) pickMusic(message.message);
        }
    }
}
