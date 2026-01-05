//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_CONSTRAINT_H
#define INTELLIGENTSYSTEM_CONSTRAINT_H

#include <string>

enum Constraint {
    DEFAULT_CONSTRAINT,
    NULLABLE,
    NOT_NULL,
};

std::string toString(const Constraint& constraint);
Constraint fromStringToConstraint(const std::string& string);

#endif //INTELLIGENTSYSTEM_CONSTRAINT_H
