//
// Created by Darian Sandru on 05.01.2026.
//

#include "Value.h"
#include <stdexcept>
#include <sstream>

Value::Value()
        : type(DEFAULT_TYPE), empty(true) {}

Value::Value(Type type, ValueData data)
        : type(type), data(std::move(data)), empty(false) {}

Type Value::getType() const {
    return type;
}

bool Value::isEmpty() const {
    return empty;
}

int Value::getINT() const {
    if (type != INT)
        throw std::runtime_error("Value is not INT");
    return std::get<int>(data);
}

float Value::getREAL() const {
    if (type != REAL)
        throw std::runtime_error("Value is not REAL");
    return std::get<float>(data);
}

long Value::getBIGINT() const {
    if (type != BIGINT)
        throw std::runtime_error("Value is not BIGINT");
    return std::get<long>(data);
}

bool Value::getBOOL() const {
    if (type != BOOL)
        throw std::runtime_error("Value is not BOOL");
    return std::get<bool>(data);
}

const std::string& Value::getTEXT() const {
    if (type != TEXT)
        throw std::runtime_error("Value is not TEXT");
    return std::get<std::string>(data);
}

const Date& Value::getDATE() const {
    if (type != DATE)
        throw std::runtime_error("Value is not DATE");
    return std::get<Date>(data);
}

std::string Value::toString() const {
    if (empty) {
        return "NULL";
    }

    switch (type) {
        case INT:
            return std::to_string(std::get<int>(data));

        case REAL: {
            std::ostringstream oss;
            oss << std::get<float>(data);
            return oss.str();
        }

        case BIGINT:
            return std::to_string(std::get<long>(data));

        case BOOL:
            return std::get<bool>(data) ? "true" : "false";

        case TEXT:
            return "'" + std::get<std::string>(data) + "'";

        case DATE:
            return std::get<Date>(data).toString();

        case DEFAULT_TYPE:
        default:
            return "NULL";
    }
}

bool Value::compareTo(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    return data == other.data;
}

bool Value::greaterThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    return data > other.data;
}

bool Value::greaterOrEqualThan(const Value& other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    return data >= other.data;
}

bool Value::lesserThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    return data < other.data;
}

bool Value::lesserOrEqualThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    return data <= other.data;
}
