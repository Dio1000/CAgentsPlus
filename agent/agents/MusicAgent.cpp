//
// Created by Darian Sandru on 07.01.2026.
//

#include "MusicAgent.h"

void MusicAgent::playMusic(const std::string& path) const {
    std::cout << "Playing music...\n";
    std::string command = "afplay \"" + path + "\"";
    std::system(command.c_str());
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
