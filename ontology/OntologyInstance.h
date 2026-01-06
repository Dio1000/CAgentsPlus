//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H
#define INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H

#include "Ontology.h"
#include "Value.h"
#include "../io/InputDevice.h"
#include "../io/OutputDevice.h"
#include "../io/FileManager.h"
#include "../helper/Logger.h"
#include <unordered_map>

class OntologyInstance {
private:
    const Ontology* ontology;
    std::unordered_map<std::string, Value> values;

public:
    explicit OntologyInstance(const Ontology* ontology);

    Ontology* getOntology() const;

    void setValue(const std::string& field, const Value& value);
    void setValue(const Field& fieldName, const Value& value);
    const Value& getValue(const std::string& field) const;
    bool hasField(const std::string& field) const;

    std::string toString() const;
    void save() const;
};

#endif //INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H
