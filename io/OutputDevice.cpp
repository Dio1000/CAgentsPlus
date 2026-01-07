//
// Created by Darian Sandru on 05.01.2026.
//

#include "OutputDevice.h"
#include "FileManager.h"
#include <fstream>
#include <iostream>

void OutputDevice::writeLines(const std::string &path, const std::vector<std::string> &lines) {
    if (path.empty()) throw std::runtime_error("File path " + path + " was not provided!");
    if (!FileManager::validFile(path)) throw std::runtime_error("File path " + path + " does not exist!");

    std::ofstream fout(path);
    for (const auto& line : lines){
        fout << line << std::endl;
    }
    fout.close();
}

void OutputDevice::writeLine(const std::string &path, const std::string &line) {
    if (path.empty()) throw std::runtime_error("File path is empty. Cannot append line.");
    if (!FileManager::validFile(path)) throw std::runtime_error("File path " + path + " does not exist!");

    std::ofstream fout(path, std::ios::app);
    fout << line << std::endl;
    fout.close();
}

void OutputDevice::write(const std::string &line) {
    std::cout << line;
}

void OutputDevice::writeNewLine(const std::string &line) {
    std::cout << line << '\n';
}

void OutputDevice::replaceLine(const std::string &path, const std::string &line) {
    if (path.empty()) throw std::runtime_error("File path is empty. Cannot append line.");
    if (!FileManager::validFile(path)) throw std::runtime_error("File path " + path + " does not exist!");

    std::ofstream fout(path, std::ios::trunc);
    fout << line << std::endl;
    fout.close();
}
