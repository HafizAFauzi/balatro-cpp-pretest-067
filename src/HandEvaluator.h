#pragma once
#include <vector>
#include "Card.h"

enum class HandRank {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush
};

class HandEvaluator {
public:
    static HandRank evaluate(const std::vector<Card>& hand);
};