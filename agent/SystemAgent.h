//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_SYSTEMAGENT_H
#define INTELLIGENTSYSTEM_SYSTEMAGENT_H

#include "message/MessageBus.h"
#include "Agent.h"
#include <thread>

class SystemAgent {
private:
    std::vector<std::unique_ptr<Agent>> agents;
    std::vector<std::thread> threads;

public:
    void addAgent(std::unique_ptr<Agent> agent);

    void start();
    void stop();
};

#endif //INTELLIGENTSYSTEM_SYSTEMAGENT_H
