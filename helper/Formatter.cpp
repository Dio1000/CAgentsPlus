//
// Created by Darian Sandru on 05.01.2026.
//

#include "Formatter.h"

void formatMeta(const std::string& path, const Ontology &ontology) {
    std::string ontologyMetaPath = path + MetaData::ONTOLOGY_META_FILE;
    std::string ontologyRowIDPath = path + MetaData::ONTOLOGY_ROWID_FILE;

    std::vector<std::string> lines;
    for (const Field& field : ontology.getFields()) {
        std::string line = field.getName() + "," + ::toString(field.getType()) + "," + ::toString(field.getConstraint());
        lines.emplace_back(line);
    }

    OutputDevice::writeLines(ontologyMetaPath, lines);
    OutputDevice::writeLine(ontologyRowIDPath, "0");
}

void Formatter::formatMetaOntology(const Ontology &ontology) {
    if (ontology.isEmpty()) {
        Logger::addWarning("Could not format ontology because it is empty!");
        return;
    }
    if (FileManager::directoryExists(ontology.getPath())) {
        Logger::addWarning("Could not format ontology as it already exists!");
        return;
    }

    std::string ontologyRootPath = ontology.getPath();
    std::string ontologyMetaPath = ontology.getPath() + MetaData::ONTOLOGY_META_FILE;
    std::string ontologyRowIDPath = ontology.getPath() + MetaData::ONTOLOGY_ROWID_FILE;
    std::string ontologyDataPath = ontology.getPath() + MetaData::ONTOLOGY_DATA_DIRECTORY;

    FileManager::createDirectory(ontologyRootPath);
    FileManager::createFile(ontologyMetaPath);
    FileManager::createFile(ontologyRowIDPath);
    FileManager::createDirectory(ontologyDataPath);

    formatMeta(ontologyRootPath, ontology);
}

void Formatter::formatDataOntology(const Ontology &ontology) {

}
