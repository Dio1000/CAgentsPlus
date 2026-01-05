//
// Created by Darian Sandru on 05.01.2026.
//

#include "Type.h"

std::string toString(const Type& type) {
    switch (type) {
        case DEFAULT_TYPE: return "DEFAULT_TYPE";
        case INT: return "INT";
        case REAL: return "REAL";
        case BIGINT: return "BIGINT";
        case DATE: return "DATE";
        case BOOL: return "BOOL";
        case TEXT: return "TEXT";
    }
}

Type fromStringToType(const std::string& string) {
    if (string == "DEFAULT_TYPE") return DEFAULT_TYPE;
    else if (string == "INT") return INT;
    else if (string == "REAL") return REAL;
    else if (string == "BIGINT") return BIGINT;
    else if (string == "DATE") return DATE;
    else if (string == "BOOL") return BOOL;
    else if (string == "TEXT") return TEXT;
    else return DEFAULT_TYPE;
}
