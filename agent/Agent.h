//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_AGENT_H
#define INTELLIGENTSYSTEM_AGENT_H

#include <thread>
#include <map>
#include "../ontology/query/decision/RuleDecision.h"
#include "../ontology/query/decision/WeightedDecision.h"
#include "../ontology/factory/OntologyFactory.h"
#include "message/MessageBus.h"
#include "AgentMetaData.h"

class Agent {
protected:
    size_t agentID;
    RuleDecision* ruleDecision;
    WeightedDecision* weightedDecision;

    std::atomic<bool> running{true};
public:
    Agent(size_t agentID, RuleDecision* ruleDecision, WeightedDecision* weightedDecision) :
        agentID(agentID), ruleDecision(ruleDecision), weightedDecision(weightedDecision) {}

    virtual ~Agent() = default;

    size_t getID() const;
    RuleDecision* getRuleDecision() const;
    WeightedDecision* getWeightedDecision() const;

    virtual void run() = 0;
    void stop() { this->running = false; }
};


#endif //INTELLIGENTSYSTEM_AGENT_H
