//
// Created by Darian Sandru on 06.01.2026.
//

#include "Operation.h"

std::string toString(const Operation& operation) {
    switch (operation) {
        case DEFAULT_OPERATION: return "DEFAULT_OPERATION";
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
    }
}

Operation fromStringToOperation(const std::string& string) {
    if (string == "DEFAULT_OPERATION") return DEFAULT_OPERATION;
    else if (string == "ADD") return ADD;
    else if (string == "SUB") return SUB;
    else if (string == "MUL") return MUL;
    else if (string == "DIV") return DIV;
    else if (string == "MOD") return MOD;
    else return DEFAULT_OPERATION;
}