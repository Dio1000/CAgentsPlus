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

void OntologyInstance::setValue(const Field &fieldName, const Value &value) {
    std::string field = fieldName.getName();

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
    if (!ontology->hasField(field)) {
        throw std::runtime_error(
                "Field '" + field + "' does not exist in ontology '" +
                ontology->getName() + "'."
        );
    }

    return values.at(field);
}

bool OntologyInstance::hasField(const std::string &field) const {
    return ontology->hasField(field);
}

std::string OntologyInstance::toString() const {
    std::string string = "{";
    size_t total = ontology->getFields().size();
    size_t index = 0;
    for (const Field& field : ontology->getFields()) {
        if (index == total - 1) string += field.getName() + "=" + this->getValue(field.getName()).toString();
        else string += field.getName() + "=" + this->getValue(field.getName()).toString() + ",";
    }

    return string.substr(0, string.length() - 1) + "}";
}

void OntologyInstance::save() const {
    std::string json = "{\n";
    std::vector<Field> fields = ontology->getFields();
    for (const Field& field : fields) {
        if (field.getConstraint() == NOT_NULL && this->getValue(field.getName()).isEmpty()) {
            throw std::runtime_error("Could not save: " + this->toString() + " as JSON. "
                                    + field.getName() + "is NOT_NULL but has no value set.");
        }

        if (field.getType() == TEXT) json += "\t'" + field.getName() + "':" + this->getValue(field.getName()).toString() + "\n";
        else json += "\t'" + field.getName() + "':'" + this->getValue(field.getName()).toString() + "'\n";
    }
    json += "}";

    std::string jsonPath = MetaData::getDataPath(ontology->getName(), MetaData::getRowID(ontology->getName()));
    FileManager::createFile(jsonPath);
    OutputDevice::writeLine(jsonPath, json);
    MetaData::incrementRowID(ontology->getName());
}

Ontology *OntologyInstance::getOntology() const {
    return const_cast<Ontology *>(this->ontology);
}
