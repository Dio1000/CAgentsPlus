//
// Created by Darian Sandru on 05.01.2026.
//

#ifndef INTELLIGENTSYSTEM_TYPE_H
#define INTELLIGENTSYSTEM_TYPE_H

#include <string>

enum Type {
    INT,
    REAL,
    BIGINT,
    DATE,
    BOOL,
    TEXT,
    DEFAULT_TYPE,
};

std::string toString(const Type& type);


#endif //INTELLIGENTSYSTEM_TYPE_H
