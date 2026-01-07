//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_FORMATTER_H
#define INTELLIGENTSYSTEM_FORMATTER_H

#include "../ontology/Ontology.h"
#include "../helper/Logger.h"
#include "../io/FileManager.h"
#include "../io/OutputDevice.h"
#include <iostream>

class Formatter {
public:
    Formatter() = delete;
    Formatter(const Formatter& other) = delete;
    Formatter& operator=(const Formatter& other) = delete;

    static void formatMetaOntology(const Ontology& ontology);
    static void formatMetaOntology(Ontology* ontology);
};


#endif //INTELLIGENTSYSTEM_FORMATTER_H
