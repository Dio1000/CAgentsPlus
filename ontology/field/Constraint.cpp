//
// Created by Darian Sandru on 05.01.2026.
//

#include "Constraint.h"

std::string toString(const Constraint& constraint) {
    switch (constraint) {
        case DEFAULT_CONSTRAINT: return "DEFAULT_CONSTRAINT";
        case NULLABLE: return "NULLABLE";
        case NOT_NULL: return "NOT_NULL";
    }
}
