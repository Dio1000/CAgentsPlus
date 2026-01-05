//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_LOGGER_H
#define INTELLIGENTSYSTEM_LOGGER_H

#include <string>
#include <vector>

class Logger {
private:
    static std::vector<std::string> errors;
    static std::vector<std::string> warnings;
public:
    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static std::vector<std::string> getErrors();
    static std::vector<std::string> getWarnings();

    static size_t getErrorCount();
    static size_t getWarningCount();

    static void addError(const std::string& error);
    static void addWarning(const std::string& warning);
};


#endif //INTELLIGENTSYSTEM_LOGGER_H
