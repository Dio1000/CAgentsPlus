//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ONTOLOGY_H
#define INTELLIGENTSYSTEM_ONTOLOGY_H

#include <string>
#include <vector>
#include "field/Field.h"
#include "../meta/MetaData.h"

class Ontology {
private:
    std::string name;
    std::string path;
    std::vector<Field> fields;
public:
    Ontology() = default;
    Ontology(const std::string& name, const std::vector<Field>& fields);

    std::string getName() const;
    std::string getPath() const;

    std::vector<Field> getFields() const;
    Field getField(int index) const;
    Field getField(const std::string& fieldName) const;

    bool hasField(const Field& field) const;
    bool hasField(const std::string& field) const;

    std::string toString() const;
    bool isEmpty() const;
};


#endif //INTELLIGENTSYSTEM_ONTOLOGY_H
