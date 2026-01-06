//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_QUERY_H
#define INTELLIGENTSYSTEM_QUERY_H

#include "../OntologyInstance.h"
#include <iostream>

class Query {
private:
    OntologyInstance* ontologyInstance;

public:
    Query() = default;
    explicit Query(OntologyInstance* instance)
            : ontologyInstance(instance) {}

    bool equalTo(const std::string& field, const Value& value) const;
    bool greaterThan(const std::string& field, const Value& value) const;
    bool greaterOrEqualThan(const std::string& field, const Value& value) const;
    bool lesserThan(const std::string& field, const Value& value) const;
    bool lesserOrEqualThan(const std::string& field, const Value& value) const;

    bool isEmpty() const;

};


#endif //INTELLIGENTSYSTEM_QUERY_H
