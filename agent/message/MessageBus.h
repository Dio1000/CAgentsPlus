//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_MESSAGEBUS_H
#define INTELLIGENTSYSTEM_MESSAGEBUS_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <iostream>
#include "Message.h"

class MessageBus {
private:
    static std::unordered_map<size_t, std::queue<Message>> mailbox;
    static std::mutex mutex;
public:
    MessageBus() = delete;
    MessageBus(const MessageBus& other) = delete;
    MessageBus(MessageBus&& other) = delete;

    static void registerAgent(size_t agentID);
    static void send(size_t receiverID, const Message& message);
    static std::queue<Message> collect(size_t agentID);
};


#endif //INTELLIGENTSYSTEM_MESSAGEBUS_H
