//
// Created by Darian Sandru on 07.01.2026.
//

#include "MusicAgent.h"

void MusicAgent::playMusic(const std::string& path) const {
    OutputDevice::writeNewLine("Music Agent, with ID: " + std::to_string(AgentMetaData::MUSIC_AGENT_ID) + ", speaking:");
    std::vector<std::string> songs = Algorithm::split(path, ',');

    for (const std::string& song : songs) {
        OutputDevice::writeNewLine("Playing song: " + song + "...");
        std::string musicPath = MetaData::OTHERS_ROOT_DIRECTORY + "/songs/" + song + ".m4a";
        std::string command = "afplay \"" + musicPath + "\"";
        std::system(command.c_str());
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
