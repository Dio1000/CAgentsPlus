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
    explicit Query(OntologyInstance* instance)
            : ontologyInstance(instance) {}

    Query(const Query& other) = delete;
    Query& operator=(const Query& other) = delete;
    Query(Query&& other) = delete;
    Query& operator=(Query&& other) = delete;

    bool equalTo(const std::string& field, const Value& value) const;
    bool greaterThan(const std::string& field, const Value& value) const;
    bool greaterOrEqualThan(const std::string& field, const Value& value) const;
    bool lesserThan(const std::string& field, const Value& value) const;
    bool lesserOrEqualThan(const std::string& field, const Value& value) const;

};


#endif //INTELLIGENTSYSTEM_QUERY_H
