//
// Created by Darian Sandru on 05.01.2026.
//

#include "Logger.h"

std::vector<std::string> Logger::errors;
std::vector<std::string> Logger::warnings;

std::vector<std::string> Logger::getErrors() {
    return errors;
}

std::vector<std::string> Logger::getWarnings() {
    return warnings;
}

size_t Logger::getErrorCount() {
    return errors.size();
}

size_t Logger::getWarningCount() {
    return warnings.size();
}

void Logger::addError(const std::string &error) {
    errors.emplace_back(error);
}

void Logger::addWarning(const std::string &warning) {
    warnings.emplace_back(warning);
}
