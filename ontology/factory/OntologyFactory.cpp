//
// Created by Darian Sandru on 05.01.2026.
//

#include "OntologyFactory.h"

namespace fs = std::filesystem;

int getDataIndex(const std::string& path) {
    size_t index = path.size() - 1;
    std::string dataString;
    while (index != 0) {
        if (path[index] == '/' || path[index] == '\\') break;
        dataString += path[index];
        index--;
    }

    std::reverse(dataString.begin(), dataString.end());
    return std::stoi(dataString);
}

Ontology* OntologyFactory::getOntology(const std::string &ontologyName) {
    std::string ontologyPath = MetaData::getMetaDataPath(ontologyName);
    std::vector<std::string> lines = InputDevice::readLines(ontologyPath);

    std::vector<Field> fields;
    for (const std::string& line : lines) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = Algorithm::split(line, ',');

        Field field = Field(tokens[0], ::fromStringToType(tokens[1]), ::fromStringToConstraint(tokens[2]));
        fields.emplace_back(field);
    }

    return new Ontology{ontologyName, fields};
}

OntologyInstance* OntologyFactory::getOntologyInstance(Ontology* ontology, int index) {
    std::string metaPath = MetaData::getMetaDataPath(ontology->getName());
    std::string dataPath = MetaData::getDataPath(ontology->getName(), index);

    std::vector<std::string> metaLines = InputDevice::readLines(metaPath);
    std::vector<std::string> dataLines = InputDevice::readLines(dataPath);

    auto* ontologyInstance = new OntologyInstance(ontology);

    int idx = 0;
    while (idx < metaLines.size()) {
        Type type = ::fromStringToType(Algorithm::split(metaLines[idx], ',')[1]);
        std::string fieldName = Algorithm::split(metaLines[idx], ',')[0];

        if (type == TEXT) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            Value value = Value(type, data.substr(1, data.size() - 2));
            ontologyInstance->setValue(fieldName, value);
        }
        else if (type == INT) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            Value value = Value(type, std::stoi(data.substr(1, data.size() - 2)));
            ontologyInstance->setValue(fieldName, value);
        }
        else if (type == BIGINT) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            Value value = Value(type, std::stol(data.substr(1, data.size() - 2)));
            ontologyInstance->setValue(fieldName, value);
        }
        else if (type == REAL) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            Value value = Value(type, std::stof(data.substr(1, data.size() - 2)));
            ontologyInstance->setValue(fieldName, value);
        }
        else if (type == BOOL) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            Value value = Value(type, data.substr(1, data.size() - 2) == "true");
            ontologyInstance->setValue(fieldName, value);
        }
        else if (type == DATE) {
            std::string data = Algorithm::split(dataLines[idx + 1], ':')[1];
            std::vector<std::string> dateParts = Algorithm::split(data.substr(1, data.size() - 2), '.');
            Value value = Value(type, Date(std::stoi(dateParts[0]), std::stoi(dateParts[1]), std::stoi(dateParts[2])));
            ontologyInstance->setValue(fieldName, value);
        }
        else {
            throw std::runtime_error("Could not create Ontology Instance. " + fieldName + " has no type!");
        }
        idx++;
    }
    return ontologyInstance;
}

std::vector<OntologyInstance*> OntologyFactory::getOntologyInstances(Ontology *ontology) {
    int rowID = MetaData::getRowID(ontology->getName());
    if (rowID == -1) {
        Logger::addWarning("No instances for Ontology: " + ontology->getName());
        return {};
    }
    std::vector<OntologyInstance*> instances;
    instances.reserve(rowID);

    std::string pathString = MetaData::ONTOLOGY_ROOT_DIRECTORY + "/" + ontology->getName() + MetaData::ONTOLOGY_DATA_DIRECTORY;
    struct stat sb{};

    for (const auto& entry : fs::directory_iterator(pathString)) {
        const std::filesystem::path& outFileName = entry.path();
        std::string outFileNameString = outFileName.string();
        const char* path = outFileNameString.c_str();

        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)) instances.emplace_back(getOntologyInstance(ontology, getDataIndex(path)));
    }
    return instances;
}
