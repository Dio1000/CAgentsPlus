//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_MUSICPICKERAGENT_H
#define INTELLIGENTSYSTEM_MUSICPICKERAGENT_H

#include "../Agent.h"
#include <string>
#include <set>

class MusicPickerAgent : public Agent {
private:
    std::vector<std::string> availableSongs;
    void setup(const std::string& message);

    void sendInfo(const std::string& message);
public:
    MusicPickerAgent(size_t agentID, RuleDecision* rd, WeightedDecision* wd)
    : Agent(agentID, rd, wd) {MessageBus::registerAgent(agentID);}

    void run() override;
    void pickMusic(const std::string& message);
};


#endif //INTELLIGENTSYSTEM_MUSICPICKERAGENT_H
