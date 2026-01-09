//
// Created by Darian Sandru on 06.01.2026.
//

#include "Weight.h"

Weight::Weight(const std::unordered_map<std::string, double>& weights) {
    this->weights = weights;
}

double Weight::getFieldWeight(const std::string& field) const {
    auto it = weights.find(field);
    return (it != weights.end()) ? it->second : 0.0;
}

void Weight::removeWeight(const std::string& weightName) {
    this->weights.erase(weightName);
}





