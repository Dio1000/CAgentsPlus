//
// Created by Darian Sandru on 05.01.2026.
//

#include "OntologyFactory.h"

Ontology OntologyFactory::getOntology(const std::string &ontologyName) {
    std::string ontologyPath = MetaData::getMetaDataPath(ontologyName);
    std::vector<std::string> lines = InputDevice::readLines(ontologyPath);

    std::vector<Field> fields;
    for (const std::string& line : lines) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = Algorithm::split(line, ',');

        Field field = Field(tokens[0], ::fromStringToType(tokens[1]), ::fromStringToConstraint(tokens[2]));
        fields.emplace_back(field);
    }

    return {ontologyName, fields};
}
