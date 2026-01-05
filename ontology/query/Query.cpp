//
// Created by Darian Sandru on 05.01.2026.
//

#include "Query.h"

bool Query::equalTo(const std::string& field, const Value& value) const {
    const Value& stored = ontologyInstance->getValue(field);
    if (stored.getType() != value.getType()) return false;

    return stored.compareTo(value);
}

bool Query::greaterThan(const std::string &field, const Value &value) const {
    const Value& stored = ontologyInstance->getValue(field);
    if (stored.getType() != value.getType()) return false;
    if (stored.getType() == TEXT || stored.getType() == BOOL) return false;

    return stored.greaterThan(value);
}

bool Query::greaterOrEqualThan(const std::string &field, const Value &value) const {
    const Value& stored = ontologyInstance->getValue(field);
    if (stored.getType() != value.getType()) return false;
    if (stored.getType() == TEXT || stored.getType() == BOOL) return false;

    return stored.greaterOrEqualThan(value);
}

bool Query::lesserThan(const std::string &field, const Value &value) const {
    const Value& stored = ontologyInstance->getValue(field);
    if (stored.getType() != value.getType()) return false;
    if (stored.getType() == TEXT || stored.getType() == BOOL) return false;

    return stored.lesserThan(value);
}

bool Query::lesserOrEqualThan(const std::string &field, const Value &value) const {
    const Value& stored = ontologyInstance->getValue(field);
    if (stored.getType() != value.getType()) return false;
    if (stored.getType() == TEXT || stored.getType() == BOOL) return false;

    return stored.lesserOrEqualThan(value);
}
