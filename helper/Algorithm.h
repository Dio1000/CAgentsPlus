//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ALGORITHM_H
#define INTELLIGENTSYSTEM_ALGORITHM_H

#include <vector>
#include <string>
#include <iostream>

class Algorithm {
public:
    Algorithm() = delete;
    Algorithm(const Algorithm& other) = delete;
    Algorithm& operator=(const Algorithm& other) = delete;

    static std::vector<std::string> split(const std::string& line, const char& regex);
    static std::string strip(const std::string& line, const char& regex);
    static void toLower(std::string& data);
};


#endif //INTELLIGENTSYSTEM_ALGORITHM_H
