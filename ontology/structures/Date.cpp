//
// Created by Darian Sandru on 05.01.2026.
//

#include "Date.h"

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

std::string Date::toString() const {
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

bool Date::compareTo(const Date& other) const {
    return (this->day == other.day && this->month == other.month && this->year == other.year);
}
