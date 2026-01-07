//
// Created by Darian Sandru on 07.01.2026.
//

#include "SystemAgent.h"

void SystemAgent::addAgent(std::unique_ptr<Agent> agent) {
    MessageBus::registerAgent(agent->getID());
    agents.push_back(std::move(agent));
}

void SystemAgent::start() {
    for (auto& agent : agents) threads.emplace_back([&]() { agent->run(); });
}

void SystemAgent::stop() {
    for (auto& agent : agents) agent->stop();
    for (auto& t : threads) t.join();
}