//
// Created by Darian Sandru on 05.01.2026.
//

#include "LogicController.h"
#include "../io/FileManager.h"
#include "../io/InputDevice.h"
#include "../io/OutputDevice.h"

#include "../helper/Logger.h"

bool LogicController::run() {
    OutputDevice::writeToScreen("---Initialising Systems---");

    bool filesValid = checkFileValidity();
    if (!filesValid) {
        OutputDevice::writeToScreen("Initialisation failure! Run --log to check issues or --doctor for quick fixes!");
        return false;
    }
    else OutputDevice::writeToScreen("File integrity checked!");

    bool agentsValid = checkAgentValidity();
    if (!agentsValid) {
        OutputDevice::writeToScreen("Initialisation failure! Run --log to check issues or --doctor for quick fixes!");
        return false;
    }
    else OutputDevice::writeToScreen("Agent integrity checked!");

    return true;
}

bool LogicController::checkFileValidity() {
    bool filesValid = true;
    if (!FileManager::directoryExists("files/ontologies")) {
        Logger::addError("Missing files/ontologies directory!");
        filesValid = false;
    }

    return filesValid;
}

bool LogicController::checkAgentValidity() {
    bool agentsValid = true;

    return agentsValid;
}
