//
// Created by Darian Sandru on 05.01.2026.
//

#include "Field.h"

Field::Field() {
    this->name = "DEFAULT";
    this->type = DEFAULT_TYPE;
    this->constraint = DEFAULT_CONSTRAINT;
}

Field::Field(const std::string& name, const Type& type, const Constraint& constraint) {
    this->name = name;
    this->type = type;
    this->constraint = constraint;
}

std::string Field::getName() const {
    return this->name;
}

Type Field::getType() const {
    return this->type;
}

Constraint Field::getConstraint() const {
    return this->constraint;
}

bool Field::isEmpty() const {
    return (this->name == "DEFAULT" && this->type == DEFAULT_TYPE && this->constraint == DEFAULT_CONSTRAINT);
}

std::string Field::toString() const {
    return "{name=" + this->name + ",type=" + ::toString(this->type) + ",constraint=" + ::toString(this->constraint) + "}";
}

bool Field::compareTo(const Field &otherField) const {
    return (this->type == otherField.type && this->constraint == otherField.constraint);
}
