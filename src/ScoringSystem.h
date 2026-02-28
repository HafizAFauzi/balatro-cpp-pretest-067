#pragma once
#include "HandEvaluator.h"

struct ScoreResult {
    int chips;
    int multiplier;
    int total;
};

class ScoringSystem {
public:
    ScoreResult calculateScore(HandRank rank) const;
};