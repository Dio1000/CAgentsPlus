//
// Created by Darian Sandru on 07.01.2026.
//

#include "MusicAgent.h"

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

void playSong(const std::string& song) {
    OutputDevice::writeNewLine("Playing song: " + song + "...");
    std::string musicPath = MetaData::OTHERS_ROOT_DIRECTORY + "/songs/" + song + ".m4a";
    std::string command = "afplay \"" + musicPath + "\"";
    std::system(command.c_str());
}

void MusicAgent::playMusic(const std::string& path) const {
    OutputDevice::writeNewLine("Music Agent, with ID: " + std::to_string(AgentMetaData::MUSIC_AGENT_ID) + ", speaking:");
    std::vector<std::string> parts = Algorithm::split(path, ':');
    std::queue<std::string> songQueue;

    if (parts[0] == "play") {
        Ontology* ontology = OntologyFactory::getOntology("song");
        std::vector<OntologyInstance*> instances = OntologyFactory::getOntologyInstances(ontology);
        std::vector<std::string> songs = Algorithm::split(parts[1], ',');

        for (OntologyInstance* instance : instances) {
            const std::string name = normalize(instance->getValue("name").getTEXT());
            if (std::find(songs.begin(), songs.end(), name) != songs.end()) {
                songQueue.push(instance->getValue("name").getTEXT());
            }
        }

        OutputDevice::writeNewLine("Playing selected songs: ");
        int index = 1;
        while (!songQueue.empty()) {
            std::string currentSong = songQueue.front();
            OutputDevice::writeNewLine(std::to_string(index) + ". " + currentSong);
            playSong(currentSong);

            songQueue.pop();
            index++;
        }
        return;
    }

    for (const std::string& song : parts) {
        playSong(song);
    }
}

void MusicAgent::run() {
    while (running) {
        auto messages = MessageBus::collect(agentID);
        while (!messages.empty()) {
            auto message = messages.front();
            messages.pop();

            if (message.type == INFO) playMusic(message.message);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
