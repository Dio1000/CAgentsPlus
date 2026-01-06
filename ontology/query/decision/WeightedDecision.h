//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_WEIGHTEDDECISION_H
#define INTELLIGENTSYSTEM_WEIGHTEDDECISION_H

#include "../Decision.h"
#include "Weight.h"

class WeightedDecision : Decision {
private:
    std::vector<OntologyInstance*> instances;
    Weight weight;
    bool ordered = false;
public:
    WeightedDecision() = default;
    WeightedDecision(const std::vector<OntologyInstance*>& instances, const Weight& weight);

    double getWeight(OntologyInstance* instance) const;
    OntologyInstance* getBestDecision() override;
    OntologyInstance* getWorstDecision() override;
    std::vector<OntologyInstance*> rankDecisions() override;
};


#endif //INTELLIGENTSYSTEM_WEIGHTEDDECISION_H
