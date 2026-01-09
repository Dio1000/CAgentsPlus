//
// Created by Darian Sandru on 09.01.2026.
//

#include "AgentMetaData.h"

size_t AgentMetaData::SYSTEM_AGENT_ID = 0;
size_t AgentMetaData::USER_AGENT_ID = 1;
size_t AgentMetaData::ANALYST_AGENT_ID = 2;
size_t AgentMetaData::MUSIC_AGENT_ID = 3;
size_t AgentMetaData::MUSIC_PICKER_AGENT_ID = 4;

bool AgentMetaData::checkIDValidity() {
    std::vector<size_t> ids =
            {SYSTEM_AGENT_ID,
             USER_AGENT_ID,
             ANALYST_AGENT_ID,
             MUSIC_AGENT_ID,
             MUSIC_PICKER_AGENT_ID};

    std::sort(ids.begin(), ids.end());
    for (int i = 1 ; i < ids.size() ; i++) {
        if (ids[i] == ids[i - 1]) {
            Logger::addError("Two agents have the same ID!");
            return false;
        }
    }
    return true;
}
