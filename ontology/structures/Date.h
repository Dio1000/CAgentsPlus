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
};


#endif //INTELLIGENTSYSTEM_DATE_H
