//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_RULEFACTORY_H
#define INTELLIGENTSYSTEM_RULEFACTORY_H


#include "../query/decision/Rule.h"
#include "../../helper/Algorithm.h"

class RuleFactory {
public:
    RuleFactory() = delete;
    RuleFactory(const RuleFactory& other) = delete;
    RuleFactory& operator=(const RuleFactory& other) = delete;

    static Rule* getRule(Ontology* ontology, const std::string& ruleName);
    static std::vector<Rule*> getRules(Ontology* ontology);
};


#endif //INTELLIGENTSYSTEM_RULEFACTORY_H
