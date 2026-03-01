#include "Blind.h"

Blind::Blind(const std::string& name, int targetScore)
    : name(name), targetScore(targetScore) {}

std::string Blind::getName() const {
    return name;
}

int Blind::getTargetScore() const {
    return targetScore;
}