//
// Created by Darian Sandru on 05.01.2026.
//

#include "Algorithm.h"

std::vector<std::string> Algorithm::split(const std::string &line, const char &regex) {
    std::string strippedLine = Algorithm::strip(line, regex);
    std::vector<std::string> output;
    std::string currentString;
    for (const char& ch : strippedLine) {
        if (ch == regex && !currentString.empty()) {
            output.emplace_back(currentString);
            currentString = "";
        }
        else currentString += ch;
    }

    if (!currentString.empty()) output.emplace_back(currentString);
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
