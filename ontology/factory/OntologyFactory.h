//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ONTOLOGYFACTORY_H
#define INTELLIGENTSYSTEM_ONTOLOGYFACTORY_H

#include <string>
#include <iostream>
#include "../Ontology.h"
#include "../../meta/MetaData.h"
#include "../../io/InputDevice.h"
#include "../../helper/Algorithm.h"
#include "../structures/Date.h"
#include "../OntologyInstance.h"

class OntologyFactory {
public:
    OntologyFactory() = delete;
    OntologyFactory(const OntologyFactory& other) = delete;
    OntologyFactory& operator=(const OntologyFactory& other) = delete;

    static Ontology* getOntology(const std::string& ontologyName);
    static OntologyInstance* getOntologyInstance(Ontology* ontology, int index);
    static std::vector<OntologyInstance*> getOntologyInstances(Ontology* ontology);
};


#endif //INTELLIGENTSYSTEM_ONTOLOGYFACTORY_H
