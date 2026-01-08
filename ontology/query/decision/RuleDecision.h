//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_RULEDECISION_H
#define INTELLIGENTSYSTEM_RULEDECISION_H

#include <string>
#include "../../OntologyInstance.h"
#include "../Query.h"
#include "../Decision.h"
#include "Rule.h"

class RuleDecision : Decision {
private:
    std::vector<OntologyInstance*> instances;
    std::vector<Rule*> rules;
    bool ordered = false;
public:
    RuleDecision() = default;
    RuleDecision(const std::vector<OntologyInstance*>& instances, const std::vector<Rule*>& rules);

    double getScore(OntologyInstance* instance) const;
    OntologyInstance* getBestDecision() override;
    OntologyInstance* getWorstDecision() override;
    std::vector<OntologyInstance*> rankDecisions() override;

    Rule* getRuleByName(const std::string& name);
};


#endif //INTELLIGENTSYSTEM_RULEDECISION_H
