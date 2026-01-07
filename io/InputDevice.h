//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_INPUTDEVICE_H
#define INTELLIGENTSYSTEM_INPUTDEVICE_H

#include <vector>
#include <string>
#include <iostream>

class InputDevice {
public:
    static std::vector<std::string> readLines(const std::string& path);
    static std::string readLine(const std::string& path, int index);
    static std::string readLineFromKeyboard();
};


#endif //INTELLIGENTSYSTEM_INPUTDEVICE_H