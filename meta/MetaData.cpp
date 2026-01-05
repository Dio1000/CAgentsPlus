//
// Created by Darian Sandru on 05.01.2026.
//

#include "MetaData.h"

std::string MetaData::FILES_ROOT_DIRECTORY = "./files";
std::string MetaData::ONTOLOGY_ROOT_DIRECTORY = MetaData::FILES_ROOT_DIRECTORY + "/ontologies";
std::string MetaData::ONTOLOGY_META_FILE = "/meta";
std::string MetaData::ONTOLOGY_DATA_DIRECTORY = "/data";

std::string MetaData::getMetaDataPath(const std::string &ontologyName) {
    return ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_META_FILE;
}

