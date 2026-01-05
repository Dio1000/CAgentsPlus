#include "FileManager.h"
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>

bool FileManager::validFile(const std::string &filePath) {
    if (filePath.empty()) {
        throw std::runtime_error("File path was not provided!");
    }

    std::ifstream fin(filePath);
    return fin.good();
}

bool FileManager::validDirectory(const std::string &dirPath) {
    if (dirPath.empty()) {
        throw std::runtime_error("Directory path was not provided!");
    }

    struct stat info {};
    if (stat(dirPath.c_str(), &info) != 0) {
        return false;
    }

    return (info.st_mode & S_IFDIR) != 0;
}

void FileManager::createFile(const std::string &path) {
    if (path.empty()) {
        throw std::runtime_error("File path was not provided!");
    }

    if (validFile(path)) return;

    std::ofstream fout(path);
    fout.close();
}

void FileManager::createDirectory(const std::string &path) {
    try {
        std::filesystem::create_directories(path);
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Could not create directory: " + path + ". Error: " + e.what());
    }
}

bool FileManager::fileExists(const std::string &path) {
    if (path.empty()) {
        throw std::runtime_error("File path was not provided!");
    }

    std::ifstream fin(path);
    return fin.good();
}

bool FileManager::directoryExists(const std::string &path) {
    if (path.empty()) {
        throw std::runtime_error("Directory path was not provided!");
    }

    return validDirectory(path);
}