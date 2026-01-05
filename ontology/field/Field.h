//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_FIELD_H
#define INTELLIGENTSYSTEM_FIELD_H

#include "Constraint.h"
#include "Type.h"

#include <string>

class Field {
private:
    std::string name;
    Type type;
    Constraint constraint;
public:
    Field();
    Field(const std::string& name, const Type& type, const Constraint& constraint);

    std::string getName() const;
    Type getType() const;
    Constraint getConstraint() const;

    bool isEmpty() const;
    bool compareTo(const Field& otherField) const;

    std::string toString() const;

};


#endif //INTELLIGENTSYSTEM_FIELD_H
