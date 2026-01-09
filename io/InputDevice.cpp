//
// Created by Darian Sandru on 05.01.2026.
//

#include "InputDevice.h"
#include "FileManager.h"
#include <fstream>
#include <stdexcept>

std::vector<std::string> InputDevice::readLines(const std::string& path) {
    if (path.empty())
        throw std::runtime_error("File path was not provided!");
    if (!FileManager::validFile(path))
        throw std::runtime_error("File path " + path + " does not exist!");

    std::ifstream fin(path);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(fin, line)) {
        lines.push_back(line);
    }

    fin.close();
    return lines;
}

std::string InputDevice::readLine(const std::string& path, int index) {
    if (path.empty())
        throw std::runtime_error("File path was not provided!");
    if (!FileManager::validFile(path))
        throw std::runtime_error("File path " + path + " does not exist!");
    if (index < 0)
        throw std::runtime_error("Line index cannot be negative!");

    std::ifstream fin(path);
    std::string line;
    int currentIndex = 0;

    while (std::getline(fin, line)) {
        if (currentIndex == index) {
            fin.close();
            return line;
        }
        currentIndex++;
    }

    fin.close();
    throw std::runtime_error("Line index out of range!");
}

std::string InputDevice::readLineFromKeyboard() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}