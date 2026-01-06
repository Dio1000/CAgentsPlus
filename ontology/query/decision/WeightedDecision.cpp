//
// Created by Darian Sandru on 06.01.2026.
//

#include "WeightedDecision.h"

WeightedDecision::WeightedDecision(const std::vector<OntologyInstance*>& instances, const Weight& weight) {
    this->instances = instances;
    this->weight = weight;
}

double WeightedDecision::getWeight(OntologyInstance* instance) const {
    double score = 0.0;

    const auto& fields = instance->getOntology()->getFields();

    for (const Field& field : fields) {
        const std::string& name = field.getName();
        if (!instance->hasField(name)) continue;

        const Value& value = instance->getValue(name);
        double fieldWeight = weight.getFieldWeight(name);

        switch (value.getType()) {
            case INT:
                score += fieldWeight * value.getINT();
                break;

            case REAL:
                score += fieldWeight * value.getREAL();
                break;

            case BIGINT:
                score += fieldWeight * static_cast<double>(value.getBIGINT());
                break;

            case BOOL:
                score += fieldWeight * (value.getBOOL() ? 1.0 : 0.0);
                break;

            default:
                break;
        }
    }

    return score;
}

OntologyInstance* WeightedDecision::getBestDecision() {
    if (!ordered) rankDecisions();
    return instances.empty() ? nullptr : instances.front();
}

OntologyInstance* WeightedDecision::getWorstDecision() {
    if (!ordered) rankDecisions();
    return instances.empty() ? nullptr : instances.back();
}

std::vector<OntologyInstance*> WeightedDecision::rankDecisions() {
    if (ordered) return instances;
    ordered = true;
    std::sort(instances.begin(), instances.end(),
              [this](const OntologyInstance* a, const OntologyInstance* b) {
                  return getWeight(const_cast<OntologyInstance *>(a)) > getWeight(const_cast<OntologyInstance *>(b));
              });

    return instances;
}
