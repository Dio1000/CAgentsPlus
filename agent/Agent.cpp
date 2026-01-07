//
// Created by Darian Sandru on 07.01.2026.
//

#include "Agent.h"

size_t Agent::getID() const {
    return agentID;
}

RuleDecision *Agent::getRuleDecision() const {
    return ruleDecision;
}

WeightedDecision *Agent::getWeightedDecision() const {
    return weightedDecision;
}
