//
// Created by Darian Sandru on 05.01.2026.
//

#include "OntologyInstance.h"

OntologyInstance::OntologyInstance(const Ontology *ontology) {
    this->ontology = ontology;
}

void OntologyInstance::setValue(const std::string& field, const Value& value) {
    if (!ontology) {
        throw std::runtime_error("OntologyInstance has no ontology assigned.");
    }

    if (!ontology->hasField(field)) {
        throw std::runtime_error(
                "Field '" + field + "' does not exist in ontology '" +
                ontology->getName() + "'."
        );
    }

    const Field& ontologyField = ontology->getField(field);
    if (!value.isEmpty() && value.getType() != ontologyField.getType()) {
        throw std::runtime_error(
                "Type mismatch for field '" + field +
                "'. Expected " + ::toString(ontologyField.getType()) +
                ", got " + ::toString(value.getType())
        );
    }

    if (ontologyField.getConstraint() == NOT_NULL && value.isEmpty()) {
        throw std::runtime_error("Expected a non-null value for NOT_NULL constrained field!");
    }

    values[field] = value;
}


const Value& OntologyInstance::getValue(const std::string& field) const {
    return values.at(field);
}