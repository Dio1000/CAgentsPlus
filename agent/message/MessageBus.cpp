//
// Created by Darian Sandru on 07.01.2026.
//

#include "MessageBus.h"

std::unordered_map<size_t, std::queue<Message>> MessageBus::mailbox;
std::mutex MessageBus::mutex;

void MessageBus::registerAgent(size_t agentID) {
    std::lock_guard<std::mutex> lock(mutex);
    mailbox.try_emplace(agentID, std::queue<Message>{});
}

void MessageBus::send(size_t receiverID, const Message& message) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = mailbox.find(receiverID);
    if (it == mailbox.end()) return;
    it->second.push(message);
}

std::queue<Message> MessageBus::collect(size_t agentID) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = mailbox.find(agentID);
    if (it == mailbox.end()) return {};

    std::queue<Message> out;
    std::swap(out, it->second);
    return out;
}


