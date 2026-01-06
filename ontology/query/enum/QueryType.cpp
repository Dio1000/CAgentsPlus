//
// Created by Darian Sandru on 06.01.2026.
//

#include "QueryType.h"

std::string toString(const QueryType& queryType) {
    switch (queryType) {
        case DEFAULT_QUERY_TYPE: return "DEFAULT_QUERY_TYPE";
        case EQUAL_TO: return "EQUAL_TO";
        case GREATER_THAN: return "GREATER_THAN";
        case GREATER_OR_EQUAL_THAN: return "GREATER_OR_EQUAL_THAN";
        case LESSER_THAN: return "LESSER_THAN";
        case LESSER_OR_EQUAL_THAN: return "LESSER_OR_EQUAL_THAN";
    }
}

QueryType fromStringToQueryType(const std::string& string) {
    if (string == "DEFAULT_QUERY_TYPE") return DEFAULT_QUERY_TYPE;
    else if (string == "EQUAL_TO") return EQUAL_TO;
    else if (string == "GREATER_THAN") return GREATER_THAN;
    else if (string == "GREATER_OR_EQUAL_THAN") return GREATER_OR_EQUAL_THAN;
    else if (string == "LESSER_THAN") return LESSER_THAN;
    else if (string == "LESSER_OR_EQUAL_THAN") return LESSER_OR_EQUAL_THAN;
    else return DEFAULT_QUERY_TYPE;
}