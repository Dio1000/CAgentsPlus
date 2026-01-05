//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_FILEMANAGER_H
#define INTELLIGENTSYSTEM_FILEMANAGER_H

#include <string>

class FileManager {
public:
    static void createFile(const std::string &path);
    static void createDirectory(const std::string &path);

    static bool fileExists(const std::string &path);
    static bool directoryExists(const std::string &path);

    static bool validFile(const std::string &path);
    static bool validDirectory(const std::string &path);
};


#endif //INTELLIGENTSYSTEM_FILEMANAGER_H