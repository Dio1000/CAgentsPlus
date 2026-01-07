//
// Created by Darian Sandru on 07.01.2026.
//

#ifndef INTELLIGENTSYSTEM_MESSAGE_H
#define INTELLIGENTSYSTEM_MESSAGE_H


#include <cstdio>
#include <string>

enum MessageType {
    INFO,
    RESPONSE,
    STOP,
};

struct Message {
    Message(size_t senderID, MessageType type, const std::string& message) :
        senderID(senderID), type(type), message(message) {}

    size_t senderID;
    MessageType type;
    std::string message;
};


#endif //INTELLIGENTSYSTEM_MESSAGE_H
