//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_OPERATION_H
#define INTELLIGENTSYSTEM_OPERATION_H

#include <string>

enum Operation {
    DEFAULT_OPERATION,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
};

std::string toString(const Operation& operation);
Operation fromStringToOperation(const std::string& string);


#endif //INTELLIGENTSYSTEM_OPERATION_H
