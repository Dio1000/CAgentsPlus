//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_OUTPUTDEVICE_H
#define INTELLIGENTSYSTEM_OUTPUTDEVICE_H

#include <vector>
#include <string>

class OutputDevice {
public:
    static void writeLines(const std::string& path, const std::vector<std::string>& lines);
    static void writeLine(const std::string& path, const std::string& line);

    static void writeToScreen(const std::string& line);

};


#endif //INTELLIGENTSYSTEM_OUTPUTDEVICE_H