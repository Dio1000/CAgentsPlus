//
// Created by Darian Sandru on 09.01.2026.
//

#ifndef INTELLIGENTSYSTEM_AGENTMETADATA_H
#define INTELLIGENTSYSTEM_AGENTMETADATA_H

#include <cstdio>
#include <vector>
#include "../helper/Logger.h"

class AgentMetaData {
public:
    static size_t SYSTEM_AGENT_ID;
    static size_t USER_AGENT_ID;
    static size_t ANALYST_AGENT_ID;
    static size_t MUSIC_AGENT_ID;
    static size_t MUSIC_PICKER_AGENT_ID;

    static bool checkIDValidity();
};


#endif //INTELLIGENTSYSTEM_AGENTMETADATA_H
