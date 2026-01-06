//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_METADATA_H
#define INTELLIGENTSYSTEM_METADATA_H

#include "../io/InputDevice.h"
#include "../io/OutputDevice.h"
#include <string>

struct MetaData {
public:
    static std::string FILES_ROOT_DIRECTORY;
    static std::string ONTOLOGY_ROOT_DIRECTORY;
    static std::string ONTOLOGY_META_FILE;
    static std::string ONTOLOGY_ROWID_FILE;
    static std::string ONTOLOGY_RULES_FILE;
    static std::string ONTOLOGY_DATA_DIRECTORY;

    static std::string getMetaDataPath(const std::string& ontologyName);
    static std::string getDataPath(const std::string& ontologyName, int value);
    static std::string getRulesPath(const std::string& ontologyName);
    static int getRowID(const std::string& ontologyName);
    static void incrementRowID(const std::string& ontologyName);
};


#endif //INTELLIGENTSYSTEM_METADATA_H
