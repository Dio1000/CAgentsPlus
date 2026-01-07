//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_MUSICAGENT_H
#define INTELLIGENTSYSTEM_MUSICAGENT_H

#include "../Agent.h"
#include <string>

class MusicAgent : public Agent {
public:
    MusicAgent(size_t agentID, RuleDecision* rd, WeightedDecision* wd)
            : Agent(agentID, rd, wd) {MessageBus::registerAgent(agentID);}

    void run() override;
    void playMusic(const std::string& path) const;
};


#endif //INTELLIGENTSYSTEM_MUSICAGENT_H
