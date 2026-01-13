//
// Created by Darian Sandru on 06.01.2026.
//

#include "Rule.h"

Rule::Rule(Ontology* ontology, const std::string &ruleName, const QueryType &query, const Operation &operation) {
    this->ontology = ontology;
    this->ruleName = ruleName;
    this->query = query;
    this->operation = operation;
}

Rule *Rule::clone() const {
    return new Rule(*this);
}

std::string Rule::getRuleName() const {
    return ruleName;
}

QueryType Rule::getQuery() const {
    return query;
}

Operation Rule::getOperation() const {
    return operation;
}

bool Rule::isEmpty() const {
    return query == DEFAULT_QUERY_TYPE && operation == DEFAULT_OPERATION;
}

void Rule::setData(const std::vector<Field> &_fields, const std::vector<Value> &_values, double _scoreValue) {
    if (_fields.size() != _values.size()) throw std::runtime_error("Rules must have an equal number of fields and values!");
    this->fields = _fields;
    this->values = _values;
    this->scoreValue = _scoreValue;
}

std::vector<Field> Rule::getFields() const {
    return fields;
}

std::vector<Value> Rule::getValues() const {
    return values;
}

double Rule::getScoreValue() const {
    return scoreValue;
}

void Rule::save() const {
    std::string ruleString = "rule:'" + this->ruleName + "'\n";
    ruleString += ::toString(this->query) + "(";

    for (size_t i = 0; i < fields.size(); ++i) {
        ruleString += "'" + fields[i].getName() + "'";
        if (i + 1 < fields.size()) ruleString += ",";
    }
    ruleString += ":";

    for (size_t i = 0; i < values.size(); ++i) {
        const Value& v = values[i];
        if (v.isWildCard()) ruleString += "<?>";
        else if (v.getType() == TEXT) ruleString += v.toString();
        else ruleString += "'" + v.toString() + "'";

        if (i + 1 < values.size()) ruleString += ",";
    }
    ruleString += ")\n";

    std::ostringstream scoreStream;
    scoreStream << std::fixed << std::setprecision(2) << scoreValue;

    ruleString += ::toString(operation) + " " + scoreStream.str() + "\n";
    std::string rulePath = MetaData::getRulesPath(ontology->getName());
    OutputDevice::writeLine(rulePath, ruleString);
}

void Rule::setField(const std::string &name, const Value &value) {
    int i = 0;
    for (const Field& field : fields) {
        if (field.getName() == name) break;
        i++;
    }

    Type type = fields[i].getType();
    switch (type) {
        case INT:
            values[i].setData(type, value.getINT());
            break;
        case REAL:
            values[i].setData(type, value.getREAL());
            break;
        case BIGINT:
            values[i].setData(type, value.getBIGINT());
            break;
        case DATE:
            values[i].setData(type, value.getDATE());
            break;
        case BOOL:
            values[i].setData(type, value.getBOOL());
            break;
        case TEXT:
            values[i].setData(type, value.getTEXT());
            break;
        case DEFAULT_TYPE:
            return;
    }
}

std::string Rule::toString() const {
    return "{ruleName='" + ruleName + "', query='" + ::toString(query) + "', operation='" + ::toString(operation) + "'}";
}