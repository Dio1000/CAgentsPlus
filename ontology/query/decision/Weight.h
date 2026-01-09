//
// Created by Darian Sandru on 06.01.2026.
//

#ifndef INTELLIGENTSYSTEM_WEIGHT_H
#define INTELLIGENTSYSTEM_WEIGHT_H

#include <unordered_map>
#include <string>

class Weight {
private:
    std::unordered_map<std::string, double> weights;

public:
    Weight() = default;
    explicit Weight(const std::unordered_map<std::string, double>& weights);

    double getFieldWeight(const std::string& field) const;
    void removeWeight(const std::string& weightName);
};

#endif //INTELLIGENTSYSTEM_WEIGHT_H
