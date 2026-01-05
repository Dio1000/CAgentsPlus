//
// Created by Darian Sandru on 05.01.2026.
//

#include "Ontology.h"

Ontology::Ontology(const std::string& name, const std::vector<Field>& fields) {
    this->name = name;
    this->path = MetaData::ONTOLOGY_ROOT_DIRECTORY + "/" + name;
    this->fields = fields;
}

std::string Ontology::getName() const {
    return this->name;
}

std::string Ontology::getPath() const {
    return this->path;
}

std::vector<Field> Ontology::getFields() const {
    return fields;
}

Field Ontology::getField(int index) const {
    return fields[index];
}

Field Ontology::getField(const std::string& fieldName) const {
    for (const Field& field : fields) {
        if (field.getName() == fieldName) return field;
    }

    return {};
}

bool Ontology::hasField(const Field& field) const {
    for (const Field& fld : fields) {
        if (fld.compareTo(field)) return true;
    }

    return false;
}

bool Ontology::hasField(const std::string &field) const {
    for (const Field& fld : fields) {
        if (fld.getName() == field) return true;
    }

    return false;
}

std::string Ontology::toString() const {
    std::string output;
    for (const Field& field : fields) {
        output += field.toString() + '\n';
    }

    return output;
}

bool Ontology::isEmpty() const {
    return this->name.empty();
}