//
// Created by Darian Sandru on 05.01.2026.
//

#include "Value.h"
#include <stdexcept>
#include <sstream>
#include <utility>

namespace {
    std::string normalize(std::string s) {
        Algorithm::toLower(s);
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());

        std::string out;
        bool prevSpace = false;
        for (char c : s) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!prevSpace) out += ' ';
                prevSpace = true;
            }
            else {
                out += c;
                prevSpace = false;
            }
        }
        return out;
    }
}

Value::Value()
        : type(DEFAULT_TYPE), empty(true) {}

Value::Value(Type type, ValueData data)
        : type(type), data(std::move(data)), empty(false) {}

Value::Value(const WildCard& wildCard) {
    this->type = DEFAULT_TYPE;
    this->empty = false;
    this->wildCard = wildCard;
}

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
    if (empty) return "NULL";
    if (isWildCard()) return "<?>";

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

    if (type == TEXT) return normalize(std::get<std::string>(data)) == normalize(std::get<std::string>(other.data));
    return data == other.data;
}

bool Value::greaterThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    if (type == TEXT) return normalize(std::get<std::string>(data)) > normalize(std::get<std::string>(other.data));
    return data > other.data;
}

bool Value::greaterOrEqualThan(const Value& other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    if (type == TEXT) return normalize(std::get<std::string>(data)) >= normalize(std::get<std::string>(other.data));
    return data >= other.data;
}

bool Value::lesserThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    if (type == TEXT) return normalize(std::get<std::string>(data)) < normalize(std::get<std::string>(other.data));
    return data < other.data;
}

bool Value::lesserOrEqualThan(const Value &other) const {
    if (empty || other.empty) return false;
    if (type != other.type) return false;

    if (type == TEXT) return normalize(std::get<std::string>(data)) <= normalize(std::get<std::string>(other.data));
    return data <= other.data;
}

bool Value::isWildCard() const {
    return !wildCard.isEmpty();
}

void Value::setData(Type _type, ValueData _data) {
    this->type = _type;
    this->data = std::move(_data);
}
