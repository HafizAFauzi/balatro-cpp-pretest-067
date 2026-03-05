#pragma once
#include "IModifier.h"

class DoubleScore : public Modifier {
public:
    void apply(ScoreResult& result, HandRank rank) override {

        result.total *= 2;
    }
};