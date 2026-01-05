//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_LOGICCONTROLLER_H
#define INTELLIGENTSYSTEM_LOGICCONTROLLER_H


class LogicController {
private:
    static bool checkFileValidity();
    static bool checkAgentValidity();
public:
    static bool run();
};


#endif //INTELLIGENTSYSTEM_LOGICCONTROLLER_H
