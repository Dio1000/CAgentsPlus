//
// Created by Darian Sandru on 09.01.2026.
//

#ifndef INTELLIGENTSYSTEM_ANALYSTAGENT_H
#define INTELLIGENTSYSTEM_ANALYSTAGENT_H

#include "../Agent.h"
#include <unordered_set>

class AnalystAgent : public Agent {
private:
    void sendInfo(const std::string& message);
    void sendResponse(const std::string& message, const size_t& receiver);
    void start(const std::string& message);
    bool analyse(const std::vector<std::string>& songs, const std::string& album,
                 const std::string& artist, const std::string& genre, const std::string& language);

public:
    AnalystAgent(size_t agentID, RuleDecision* rd, WeightedDecision* wd)
    : Agent(agentID, rd, wd) {MessageBus::registerAgent(agentID);}

    void run() override;
};


#endif //INTELLIGENTSYSTEM_ANALYSTAGENT_H
