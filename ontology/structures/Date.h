//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_DATE_H
#define INTELLIGENTSYSTEM_DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() = default;
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString() const;
    bool compareTo(const Date& other) const;

    bool operator==(const Date& other) const {
        return compareTo(other);
    }

    bool operator>(const Date& other) const {
        if (this->year > other.year) return true;
        else if (this->month > other.month) return true;
        return this->day > other.day;
    }

    bool operator>=(const Date& other) const {
        if (this->year > other.year) return true;
        else if (this->month > other.month) return true;
        return this->day >= other.day;
    }

    bool operator<(const Date& other) const {
        if (this->year < other.year) return true;
        else if (this->month < other.month) return true;
        return this->day < other.day;
    }

    bool operator<=(const Date& other) const {
        if (this->year < other.year) return true;
        else if (this->month < other.month) return true;
        return this->day <= other.day;
    }
};


#endif //INTELLIGENTSYSTEM_DATE_H
