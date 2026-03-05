#pragma once
#include "IModifier.h"

class PairBooster : public Modifier {
public:
    void apply(ScoreResult& result, HandRank rank) override {

        if(rank == HandRank::OnePair)
        {
            result.multiplier += 1;
            result.total = result.chips * result.multiplier;
        }
    }
};