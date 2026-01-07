//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_MUSICPICKERAGENT_H
#define INTELLIGENTSYSTEM_MUSICPICKERAGENT_H

#include "../Agent.h"
#include <string>

class MusicPickerAgent : public Agent {
public:
    MusicPickerAgent(size_t agentID, RuleDecision* rd, WeightedDecision* wd)
    : Agent(agentID, rd, wd) {MessageBus::registerAgent(agentID);}

    void run() override;
    void pickMusic() const;
};


#endif //INTELLIGENTSYSTEM_MUSICPICKERAGENT_H
