//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_QUERYTYPE_H
#define INTELLIGENTSYSTEM_QUERYTYPE_H

#include <string>

enum QueryType {
    DEFAULT_QUERY_TYPE,
    EQUAL_TO,
    GREATER_THAN,
    GREATER_OR_EQUAL_THAN,
    LESSER_THAN,
    LESSER_OR_EQUAL_THAN
};

std::string toString(const QueryType& queryType);
QueryType fromStringToQueryType(const std::string& string);

#endif //INTELLIGENTSYSTEM_QUERYTYPE_H
