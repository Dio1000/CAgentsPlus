//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H
#define INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H

#include "Ontology.h"
#include "Value.h"
#include <unordered_map>

class OntologyInstance {
private:
    const Ontology* ontology;
    std::unordered_map<std::string, Value> values;

public:
    explicit OntologyInstance(const Ontology* ontology);

    void setValue(const std::string& field, const Value& value);
    const Value& getValue(const std::string& field) const;
};

#endif //INTELLIGENTSYSTEM_ONTOLOGYINSTANCE_H
