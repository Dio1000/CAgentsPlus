//
// Created by Darian Sandru on 08.01.2026.
//

#ifndef INTELLIGENTSYSTEM_WILDCARD_H
#define INTELLIGENTSYSTEM_WILDCARD_H

#include <string>

class WildCard {
private:
    std::string value;
public:
    WildCard() = default;
    explicit WildCard(const std::string& value);

    bool isEmpty() const {
        return value.empty();
    }
};


#endif //INTELLIGENTSYSTEM_WILDCARD_H
