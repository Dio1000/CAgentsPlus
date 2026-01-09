//
// Created by Darian Sandru on 05.01.2026.
//

#include "Algorithm.h"

std::vector<std::string> Algorithm::split(const std::string& line, char delimiter) {
    std::vector<std::string> output;
    std::string current;
    for (char ch : line) {
        if (ch == delimiter) {
            output.push_back(current);
            current.clear();
        }
        else current += ch;
    }
    output.push_back(current);
    return output;
}

std::string Algorithm::strip(const std::string &line, const char& regex) {
    std::string newString;
    size_t startIndex = 0;
    size_t endIndex = line.size() - 1;

    while (line[startIndex] == regex && line[endIndex] == regex) {
        if (line[startIndex] == regex) startIndex++;
        if (line[endIndex] == regex) endIndex--;
    }

    if (startIndex == 0 && endIndex == line.size() - 1) return line;

    for (size_t i = startIndex ; i < endIndex + 1 ; i++) {
        newString += line[i];
    }
    return newString;
}

void Algorithm::toLower(std::string &data) {
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}

void Algorithm::toUpper(std::string &data) {
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c){ return std::toupper(c); });
}
