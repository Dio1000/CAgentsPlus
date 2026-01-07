//
// Created by Darian Sandru on 05.01.2026.
//

#include "LogicController.h"
#include "../ontology/factory/OntologyFactory.h"
#include "../ontology/factory/RuleFactory.h"
#include "../agent/agents/MusicAgent.h"
#include "../agent/agents/MusicPickerAgent.h"

bool LogicController::checkFileValidity() {
    bool filesValid = true;
    if (!FileManager::directoryExists(MetaData::FILES_ROOT_DIRECTORY + "/ontologies")) {
        Logger::addError("Missing files/ontologies directory!");
        filesValid = false;
    }
    if (!FileManager::directoryExists(MetaData::FILES_ROOT_DIRECTORY + "/others")) {
        Logger::addError("Missing files/others directory!");
        filesValid = false;
    }

    return filesValid;
}

bool LogicController::checkAgentValidity() {
    bool agentsValid = true;

    return agentsValid;
}

bool LogicController::checkValidity() {
    OutputDevice::writeNewLine("---Checking Systems---");

    bool filesValid = checkFileValidity();
    if (!filesValid) {
        OutputDevice::writeNewLine("Initialisation failure! Run --log to check issues or --doctor for quick fixes!");
        return false;
    }
    else OutputDevice::writeNewLine("File integrity checked!");

    bool agentsValid = checkAgentValidity();
    if (!agentsValid) {
        OutputDevice::writeNewLine("Initialisation failure! Run --log to check issues or --doctor for quick fixes!");
        return false;
    }
    else OutputDevice::writeNewLine("Agent integrity checked!");

    OutputDevice::writeNewLine("---Systems Checked---\n");
    return true;
}

void LogicController::init(const std::string& flag) {
    if (!checkValidity()) return;

    if (flag == "ontology") createOntology();
    else if (flag == "instance") createInstance();
    else if (flag == "rule") createRule();
}

void LogicController::createOntology() {
    std::string ontologyName;
    bool validName;
    do {
        OutputDevice::write("Ontology name: ");
        ontologyName = InputDevice::readLineFromKeyboard();
        std::string ontologyPath = MetaData::ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName;
        validName = !FileManager::directoryExists(ontologyPath);

        if (!validName) OutputDevice::writeNewLine("Ontology '" + ontologyName + "' already exists!");
    } while (!validName);

    std::vector<Field> fields;
    int index = 1;
    while(true) {
        OutputDevice::write("Field" + std::to_string(index) + " name: ");
        std::string fieldName = InputDevice::readLineFromKeyboard();

        OutputDevice::write("Field" + std::to_string(index) + " type: ");
        std::string typeString = InputDevice::readLineFromKeyboard();
        Type type = ::fromStringToType(typeString);

        OutputDevice::write("Field" + std::to_string(index) + " constraint: ");
        std::string constraintString = InputDevice::readLineFromKeyboard();
        Constraint constraint = ::fromStringToConstraint(constraintString);

        if (type == DEFAULT_TYPE) {
            OutputDevice::writeNewLine("Could not create Field! Type '" + typeString + "' is not a valid type!");
            continue;
        }
        else if (constraint == DEFAULT_CONSTRAINT) {
            OutputDevice::writeNewLine("Could not create Field! Constraint '" + typeString + "' is not a valid constraint!");
            continue;
        }
        else {
            fields.emplace_back(fieldName, type, constraint);
            OutputDevice::writeNewLine("Field created successfully!");
            OutputDevice::write("Create new field? (Y/n): ");

            std::string response = InputDevice::readLineFromKeyboard();
            Algorithm::toLower(response);
            if (response == "y" || response == "yes") {
                OutputDevice::writeNewLine("");
                index++;
                continue;
            }
            else break;
        }
    }

    auto* ontology = new Ontology(ontologyName, fields);
    Formatter::formatMetaOntology(ontology);
    OutputDevice::writeNewLine("Ontology '" + ontologyName + "' created successfully!");

    delete ontology;
}

void LogicController::createInstance() {
    std::string ontologyName;
    bool validName;
    do {
        OutputDevice::write("Ontology name to create instance for: ");
        ontologyName = InputDevice::readLineFromKeyboard();
        std::string ontologyPath = MetaData::ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName;
        validName = FileManager::directoryExists(ontologyPath);

        if (!validName) OutputDevice::writeNewLine("Ontology '" + ontologyName + "' does not exist!");
    } while (!validName);

    Ontology* ontology = OntologyFactory::getOntology(ontologyName);
    std::vector<Field> fields = ontology->getFields();

    auto *ontologyInstance = new OntologyInstance(ontology);
    for (const Field& field: fields) {
        std::string fieldName = field.getName();
        Type type = field.getType();
        Constraint constraint = field.getConstraint();
        OutputDevice::write("Data for field '" + fieldName
            + "' (" + ::toString(type) + ", " + ::toString(constraint) + "): ");

        std::string value = InputDevice::readLineFromKeyboard();
        int day = -1;
        int month = -1;
        int year = -1;
        if (type == DATE) {
            std::vector<std::string> dateParts = Algorithm::split(value, '.');
            day = std::stoi(dateParts[0]);
            month = std::stoi(dateParts[1]);
            year = std::stoi(dateParts[2]);
        }

        switch (type) {
            case INT:
                ontologyInstance->setValue(fieldName, {type, std::stoi(value)});
                break;
            case REAL:
                ontologyInstance->setValue(fieldName, {type, std::stof(value)});
                break;
            case BIGINT:
                ontologyInstance->setValue(fieldName, {type, std::stol(value)});
                break;
            case DATE:
                ontologyInstance->setValue(fieldName, {type, Date(day, month, year)});
                break;
            case BOOL:
                ontologyInstance->setValue(fieldName, {type, (value == "1" || value == "true")});
                break;
            case TEXT:
                ontologyInstance->setValue(fieldName, {type, value});
                break;
            case DEFAULT_TYPE:
                OutputDevice::writeNewLine("Cannot create instance for this ontology because field '" + fieldName + "' has an invalid type!");
                break;
        }
    }
    ontologyInstance->save();
    OutputDevice::writeNewLine("Ontology Instance created successfully!");
    delete ontologyInstance;
}

void LogicController::createRule() {
    std::string ontologyName;
    bool validName;
    do {
        OutputDevice::write("Ontology name to create Rule for: ");
        ontologyName = InputDevice::readLineFromKeyboard();
        std::string ontologyPath = MetaData::ONTOLOGY_ROOT_DIRECTORY + "/" + ontologyName;
        validName = FileManager::directoryExists(ontologyPath);

        if (!validName) OutputDevice::writeNewLine("Ontology '" + ontologyName + "' does not exist!");
    } while (!validName);

    Ontology* ontology = OntologyFactory::getOntology(ontologyName);
    std::vector<Field> fields = ontology->getFields();

    std::string ruleName;
    do {
        OutputDevice::write("Rule name: ");
        ruleName = InputDevice::readLineFromKeyboard();
        if (ruleName.empty()) OutputDevice::writeNewLine("Please provide a Rule name!");
    } while(ruleName.empty());

    QueryType queryType = DEFAULT_QUERY_TYPE;
    do {
        OutputDevice::write("Query type: ");
        std::string queryTypeString = InputDevice::readLineFromKeyboard();
        if (::fromStringToQueryType(queryTypeString) == DEFAULT_QUERY_TYPE) {
            OutputDevice::writeNewLine("Query type '" + queryTypeString + "' is invalid!");
        }
        else queryType = ::fromStringToQueryType(queryTypeString);
    } while(queryType == DEFAULT_QUERY_TYPE);

    std::vector<Field> fieldNames;
    do {
        OutputDevice::write("Arguments (separated by comma if more than one): ");
        std::string fieldNamesString = InputDevice::readLineFromKeyboard();
        std::vector<std::string> fieldNamesParts = Algorithm::split(fieldNamesString, ',');

        bool validFields = true;
        for (const std::string& part : fieldNamesParts) {
            std::string sanitisedField = Algorithm::strip(part, ' ');
            Field field = MetaData::getField(ontology, sanitisedField);
            if (field.isEmpty()) {
                OutputDevice::writeNewLine("Field '" + sanitisedField + "' does not exist in ontology '" + ontology->getName() + " '!");
                validFields = false;
            }
            fieldNames.emplace_back(field);
        }

        if (!validFields) fieldNames = {};
    } while (fieldNames.empty());

    std::vector<Value> valueNames;
    do {
        OutputDevice::write("Values of arguments (separated by comma if more than one): ");
        std::string valueNamesString = InputDevice::readLineFromKeyboard();
        std::vector<std::string> valueNamesParts = Algorithm::split(valueNamesString, ',');
        if (valueNamesParts.size() != fieldNames.size()) {
            OutputDevice::writeNewLine("Number of values does not match number of arguments!");
            continue;
        }

        bool validValues = true;
        for (int i = 0 ; i < valueNamesParts.size() ; i++) {
            std::string sanitisedValue = Algorithm::strip(valueNamesParts[i], ' ');
            Type currentType = fields[i].getType();
            int day = -1;
            int month = -1;
            int year = -1;
            if (currentType == DATE) {
                std::vector<std::string> dateParts = Algorithm::split(sanitisedValue, '.');
                day = std::stoi(dateParts[0]);
                month = std::stoi(dateParts[1]);
                year = std::stoi(dateParts[2]);
            }

            Value value;
            switch (currentType) {
                case INT:
                    value = {currentType, std::stoi(sanitisedValue)};
                    break;
                case REAL:
                    value = {currentType, std::stof(sanitisedValue)};
                    break;
                case BIGINT:
                    value = {currentType, std::stol(sanitisedValue)};
                    break;
                case DATE:
                    value = {currentType, Date(day, month, year)};
                    break;
                case BOOL:
                    value = {currentType, (sanitisedValue == "1" || sanitisedValue == "true")};
                    break;
                case TEXT:
                    value = {currentType, sanitisedValue};
                    break;
                case DEFAULT_TYPE:
                    OutputDevice::writeNewLine("Cannot create instance for this ontology because field '" + fields[i].getName() + "' has an invalid type!");
                    validValues = false;
                    break;
            }
            valueNames.emplace_back(value);
        }
        if (!validValues) valueNames = {};
    } while (valueNames.empty());

    Operation operation = DEFAULT_OPERATION;
    do {
        OutputDevice::write("Operation: ");
        std::string operationString = InputDevice::readLineFromKeyboard();
        if (::fromStringToOperation(operationString) == DEFAULT_OPERATION) {
            OutputDevice::writeNewLine("Operation '" + operationString + "' is invalid!");
        }
        else operation = ::fromStringToOperation(operationString);
    } while(operation == DEFAULT_OPERATION);

    double value = -1.0;
    while (true) {
        OutputDevice::write("Operation value: ");
        std::string input = InputDevice::readLineFromKeyboard();
        try {
            size_t pos = 0;
            value = std::stod(input, &pos);
            if (pos != input.size()) throw std::invalid_argument("Trailing characters");
            break;
        }
        catch (const std::exception&) {
            OutputDevice::writeNewLine("Value should be a floating point number!");
        }
    }

    Rule rule = {ontology, ruleName, queryType, operation};
    rule.setData(fieldNames, valueNames, value);
    rule.save();
    OutputDevice::writeNewLine("Rule '" + ruleName + "' was saved successfully!");

    delete ontology;
}

void LogicController::run() {
    if (!checkValidity()) return;

    Ontology* ontology = OntologyFactory::getOntology("album");
    auto instances = OntologyFactory::getOntologyInstances(ontology);
    auto rules = RuleFactory::getRules(ontology);

    RuleDecision decision(instances, rules);
    SystemAgent system;

    auto musicAgent = std::make_unique<MusicAgent>(1, &decision, nullptr);
    auto musicPickerAgent = std::make_unique<MusicPickerAgent>(2, &decision, nullptr);
    system.addAgent(std::move(musicAgent));
    system.addAgent(std::move(musicPickerAgent));

    MessageBus::send(2, Message{0, INFO, "PICK"});
    system.start();
    std::this_thread::sleep_for(std::chrono::seconds(1000));
}