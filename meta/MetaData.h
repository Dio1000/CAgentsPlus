//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_METADATA_H
#define INTELLIGENTSYSTEM_METADATA_H

#include <string>

struct MetaData {
public:
    static std::string FILES_ROOT_DIRECTORY;
    static std::string ONTOLOGY_ROOT_DIRECTORY;
    static std::string ONTOLOGY_META_FILE;
    static std::string ONTOLOGY_DATA_DIRECTORY;

    static std::string getMetaDataPath(const std::string& ontologyName);
};


#endif //INTELLIGENTSYSTEM_METADATA_H
