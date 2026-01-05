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
