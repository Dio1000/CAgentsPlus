//
// Created by Darian Sandru on 06.01.2026.
//

#include "RuleFactory.h"

std::string stripQuotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '\'' && s.back() == '\'')
        return s.substr(1, s.size() - 2);
    return s;
}

Rule* getRuleFromLines(Ontology* ontology, const std::vector<std::string>& lines) {
    std::string ruleName = stripQuotes(Algorithm::split(lines[0], ':')[1]);
    std::vector<std::string> queryParts = Algorithm::split(lines[1], '(');
    QueryType queryType = ::fromStringToQueryType(queryParts[0]);

    std::string insideParens = queryParts[1].substr(0, queryParts[1].find(')'));
    std::vector<std::string> argParts = Algorithm::split(insideParens, ':');
    std::vector<std::string> fieldNames = Algorithm::split(argParts[0], ',');
    std::vector<std::string> valueStrings = Algorithm::split(argParts[1], ',');

    std::vector<std::string> operationParts = Algorithm::split(lines[2], ' ');
    Operation operation = ::fromStringToOperation(operationParts[0]);
    double scoreValue = std::stod(operationParts[1]);

    Rule* rule = new Rule(ontology, ruleName, queryType, operation);
    std::vector<Field> fields;
    std::vector<Value> values;

    for (size_t i = 0; i < fieldNames.size(); ++i) {
        std::string fieldName = stripQuotes(fieldNames[i]);
        std::string rawValue = stripQuotes(valueStrings[i]);

        const Field& ontologyField = ontology->getField(fieldName);
        fields.push_back(ontologyField);

        if (rawValue == "<?>") {
            values.emplace_back(WildCard("value"));
        }
        else values.emplace_back(ontologyField.getType(), rawValue);
    }
    rule->setData(fields, values, scoreValue);
    return rule;
}

Rule* RuleFactory::getRule(Ontology *ontology, const std::string &ruleName) {
    std::string rulePath = MetaData::getRulesPath(ontology->getName());
    std::vector<std::string> lines = InputDevice::readLines(rulePath);

    for (int index = 0 ; index < lines.size() ; index++ ) {
        std::string line = lines[index];
        if (line.rfind("rule", 0) == 0) {
            std::vector<std::string> parts = Algorithm::split(line, ':');
            if (Algorithm::strip(parts[1], ' ') == "'" + ruleName + "'") {
                std::vector<std::string> ruleLines = {lines[index], lines[index + 1], lines[index + 2]};
                return getRuleFromLines(ontology, ruleLines);
            }
        }
    }

    return {};
}

std::vector<Rule*> RuleFactory::getRules(Ontology *ontology) {
    std::string rulePath = MetaData::getRulesPath(ontology->getName());
    std::vector<std::string> lines = InputDevice::readLines(rulePath);
    std::vector<Rule*> rules;

    int index = 0;
    while (index < lines.size()) {
        std::string line = lines[index];
        if (line.rfind("rule", 0) == 0) {
            std::vector<std::string> ruleLines = {lines[index], lines[index + 1], lines[index + 2]};
            rules.emplace_back(getRuleFromLines(ontology, ruleLines));
        }
        index++;
    }
    return rules;
}
