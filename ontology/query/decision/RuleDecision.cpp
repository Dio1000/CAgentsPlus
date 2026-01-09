//
// Created by Darian Sandru on 06.01.2026.
//

#include "RuleDecision.h"

RuleDecision::RuleDecision(const std::vector<OntologyInstance*>& instances, const std::vector<Rule*>& rules) {
    this->instances = instances;
    this->rules = rules;
}

void modifyScore(double& score, const double& value, Operation operation) {
    switch (operation) {
        case DEFAULT_OPERATION:
            throw std::runtime_error("Could not get score for Instance. Rule operation does not have a value.");
        case ADD:
            score += value;
            break;
        case SUB:
            score -= value;
            break;
        case MUL:
            score *= value;
            break;
        case DIV:
            score /= value;
            break;
        case MOD:
            score = (int)score % (int)value;
            break;
    }
}

double RuleDecision::getScore(OntologyInstance* instance) const {
    auto query = Query(instance);
    double score = 0;

    for (auto rule : rules) {
        QueryType ruleQuery = rule->getQuery();
        Operation ruleOperation = rule->getOperation();

        switch (ruleQuery) {
            case DEFAULT_QUERY_TYPE:
                throw std::runtime_error("Could not get score for Instance: " + instance->toString() + ". Query does not have a value.");
            case EQUAL_TO:
                if (query.equalTo(rule->getFields()[0].getName(), rule->getValues()[0]))
                    modifyScore(score, rule->getScoreValue(), ruleOperation);
                break;
            case GREATER_THAN:
                if (query.greaterThan(rule->getFields()[0].getName(), rule->getValues()[0]))
                    modifyScore(score, rule->getScoreValue(), ruleOperation);
                break;
            case GREATER_OR_EQUAL_THAN:
                if (query.greaterOrEqualThan(rule->getFields()[0].getName(), rule->getValues()[0]))
                    modifyScore(score, rule->getScoreValue(), ruleOperation);
                break;
            case LESSER_THAN:
                if (query.lesserThan(rule->getFields()[0].getName(), rule->getValues()[0]))
                    modifyScore(score, rule->getScoreValue(), ruleOperation);
                break;
            case LESSER_OR_EQUAL_THAN:
                if (query.lesserOrEqualThan(rule->getFields()[0].getName(), rule->getValues()[0]))
                    modifyScore(score, rule->getScoreValue(), ruleOperation);
                break;
        }
    }
    return score;
}

OntologyInstance *RuleDecision::getBestDecision() {
    if (!ordered) rankDecisions();
    return instances.empty() ? nullptr : instances.front();
}

OntologyInstance *RuleDecision::getWorstDecision() {
    if (!ordered) rankDecisions();
    return instances.empty() ? nullptr : instances.back();
}

std::vector<OntologyInstance*> RuleDecision::rankDecisions() {
    if (ordered) return instances;
    ordered = true;
    std::sort(instances.begin(), instances.end(),
              [this](const OntologyInstance* a, const OntologyInstance* b) {
                  return getScore(const_cast<OntologyInstance *>(a)) > getScore(const_cast<OntologyInstance *>(b));
              });

    return instances;
}

Rule *RuleDecision::getRuleByName(const std::string &name) {
    for (Rule* rule : rules) {
        if (rule->getRuleName() == name) return rule;
    }
    return nullptr;
}

void RuleDecision::removeRuleByName(const std::string &name) {
    int index = 0;
    for (Rule* rule : rules) {
        if (rule->getRuleName() == name) {
            rules.erase(rules.begin() + index);
            return;
        }
        index++;
    }
}

