#pragma once
#include <string>

class Blind {
private:
    std::string name;
    int targetScore;

public:
    Blind(const std::string& name, int targetScore);

    std::string getName() const;
    int getTargetScore() const;
};