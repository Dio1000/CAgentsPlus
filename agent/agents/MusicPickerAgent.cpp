//
// Created by Darian Sandru on 07.01.2026.
//

#include "MusicPickerAgent.h"

void MusicPickerAgent::pickMusic() const {
    std::cout << "Picking music...\n";
    std::string songPath = MetaData::FILES_ROOT_DIRECTORY + "/others/" + ruleDecision->getWorstDecision()->getValue("name").getTEXT() + ".m4a";
    Message message = Message(agentID, INFO, songPath);
    MessageBus::send(1, message);
}

void MusicPickerAgent::run() {
    while (running) {
        auto messages = MessageBus::collect(agentID);
        while (!messages.empty()) {
            auto message = messages.front();
            messages.pop();

            if (message.type == INFO && message.message == "PICK") pickMusic();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}