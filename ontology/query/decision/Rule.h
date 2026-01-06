//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_RULE_H
#define INTELLIGENTSYSTEM_RULE_H

#include <string>
#include <vector>
#include "../enum/QueryType.h"
#include "../enum/Operation.h"
#include "../../field/Field.h"
#include "../../Value.h"
#include <iostream>

class Rule {
private:
    std::string ruleName;
    QueryType query = DEFAULT_QUERY_TYPE;
    Operation operation = DEFAULT_OPERATION;

    std::vector<Field> fields;
    std::vector<Value> values;
    double scoreValue;
public:
    Rule() = default;
    Rule(const std::string& ruleName, const QueryType& query, const Operation& operation);

    std::string getRuleName() const;
    QueryType getQuery() const;
    Operation getOperation() const;

    void setData(const std::vector<Field>& fields, const std::vector<Value>& values, double scoreValue);
    std::vector<Field> getFields() const;
    std::vector<Value> getValues() const;
    double getScoreValue() const;

    bool isEmpty() const;
};


#endif //INTELLIGENTSYSTEM_RULE_H
