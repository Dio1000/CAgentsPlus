//
// Created by Darian Sandru on 09.01.2026.
//

#ifndef INTELLIGENTSYSTEM_USERAGENT_H
#define INTELLIGENTSYSTEM_USERAGENT_H

#include "../Agent.h"

class UserAgent : public Agent {
private:
    void getInfo(const std::string& songString);
    void sendInfo(const std::string& songString, const std::string& messageString);
    void start();

public:
    UserAgent(size_t agentID, RuleDecision* rd, WeightedDecision* wd)
    : Agent(agentID, rd, wd) {MessageBus::registerAgent(agentID);}

    void run() override;
};


#endif //INTELLIGENTSYSTEM_USERAGENT_H
