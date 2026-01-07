//
// Created by Darian Sandru on 05.01.2026.
//

#include "MetaData.h"
#include "../ontology/Ontology.h"

std::string MetaData::FILES_ROOT_DIRECTORY = "./files";
std::string MetaData::ONTOLOGY_ROOT_DIRECTORY = MetaData::FILES_ROOT_DIRECTORY + "/ontologies";
std::string MetaData::ONTOLOGY_META_FILE = "/meta";
std::string MetaData::ONTOLOGY_ROWID_FILE = "/rowID";
std::string MetaData::ONTOLOGY_RULES_FILE = "/rules";
std::string MetaData::ONTOLOGY_DATA_DIRECTORY = "/data";

std::string MetaData::getMetaDataPath(const std::string &ontologyName) {
    return ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_META_FILE;
}

std::string MetaData::getDataPath(const std::string &ontologyName, int value) {
    return ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_DATA_DIRECTORY + "/" + std::to_string(value);
}

std::string MetaData::getRulesPath(const std::string& ontologyName) {
    return ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_RULES_FILE;
}

int MetaData::getRowID(const std::string &ontologyName) {
    std::string rowIDPath = ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_ROWID_FILE;
    std::string value = InputDevice::readLine(rowIDPath, 0);

    return std::stoi(value);
}

void MetaData::incrementRowID(const std::string& ontologyName) {
    std::string rowIDPath = ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName + ONTOLOGY_ROWID_FILE;
    int currentRowID = getRowID(ontologyName);
    currentRowID++;

    OutputDevice::replaceLine(rowIDPath, std::to_string(currentRowID));
}

Field MetaData::getField(Ontology *ontology, const std::string &fieldName) {
    std::string metaDataPath = getMetaDataPath(ontology->getName());
    std::vector<std::string> lines = InputDevice::readLines(metaDataPath);

    for (const std::string& line : lines) {
        if (line.rfind(fieldName, 0) == 0) {
            std::vector<std::string> parts = Algorithm::split(line, ',');
            return {parts[0], ::fromStringToType(parts[1]), ::fromStringToConstraint(parts[2])};
        }
    }
    return {};
}
