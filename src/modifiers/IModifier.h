#pragma once
#include "../HandEvaluator.h"
#include "../ScoringSystem.h"

class Modifier {
public:
    virtual void apply(ScoreResult& result, HandRank rank) = 0;
    virtual ~Modifier() {}
};