//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_LOGICCONTROLLER_H
#define INTELLIGENTSYSTEM_LOGICCONTROLLER_H

#include "../meta/MetaData.h"
#include "../io/FileManager.h"
#include "../io/InputDevice.h"
#include "../io/OutputDevice.h"
#include "../helper/Logger.h"
#include "../agent/Agent.h"
#include "../agent/SystemAgent.h"
#include "../helper/Formatter.h"

class LogicController {
private:
    static bool checkFileValidity();
    static bool checkAgentValidity();

    static void createOntology();
    static void createInstance();
    static void createRule();
public:
    static bool checkValidity();
    static void init(const std::string& flag);
    static void run();
};


#endif //INTELLIGENTSYSTEM_LOGICCONTROLLER_H
