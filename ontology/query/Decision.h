//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_DECISION_H
#define INTELLIGENTSYSTEM_DECISION_H

#include "../OntologyInstance.h"

class Decision {
public:
    virtual OntologyInstance* getBestDecision() = 0;
    virtual OntologyInstance* getWorstDecision() = 0;
    virtual std::vector<OntologyInstance*> rankDecisions() = 0;
};


#endif //INTELLIGENTSYSTEM_DECISION_H
