//
// Created by Darian Sandru on 06.01.2026.
//

#include "Rule.h"

Rule::Rule(const std::string &ruleName, const QueryType &query, const Operation &operation) {
    this->ruleName = ruleName;
    this->query = query;
    this->operation = operation;
}

std::string Rule::getRuleName() const {
    return ruleName;
}

QueryType Rule::getQuery() const {
    return query;
}

Operation Rule::getOperation() const {
    return operation;
}

bool Rule::isEmpty() const {
    return query == DEFAULT_QUERY_TYPE && operation == DEFAULT_OPERATION;
}

void Rule::setData(const std::vector<Field> &_fields, const std::vector<Value> &_values, double _scoreValue) {
    this->fields = _fields;
    this->values = _values;
    this->scoreValue = _scoreValue;
}

std::vector<Field> Rule::getFields() const {
    return fields;
}

std::vector<Value> Rule::getValues() const {
    return values;
}

double Rule::getScoreValue() const {
    return scoreValue;
}
