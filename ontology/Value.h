#ifndef INTELLIGENTSYSTEM_VALUE_H
#define INTELLIGENTSYSTEM_VALUE_H

#include <variant>
#include <string>
#include <iostream>
#include "structures/Date.h"
#include "field/Type.h"

using ValueData = std::variant<
        int,
        float,
        long,
        bool,
        std::string,
        Date
>;

class Value {
private:
    Type type;
    ValueData data;
    bool empty;

public:
    Value();
    Value(Type type, ValueData data);

    Type getType() const;
    bool isEmpty() const;

    int getINT() const;
    float getREAL() const;
    long getBIGINT() const;
    bool getBOOL() const;
    const std::string& getTEXT() const;
    const Date& getDATE() const;

    std::string toString() const;

    bool compareTo(const Value& other) const;
    bool greaterThan(const Value& other) const;
    bool greaterOrEqualThan(const Value& other) const;
    bool lesserThan(const Value& other) const;
    bool lesserOrEqualThan(const Value& other) const;
};

#endif
