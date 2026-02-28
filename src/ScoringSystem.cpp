#include "ScoringSystem.h"

ScoreResult ScoringSystem::calculateScore(HandRank rank) const {

    int chips = 0;
    int mult = 1;

    switch(rank) {

        case HandRank::HighCard:
            chips = 5; mult = 1; break;

        case HandRank::OnePair:
            chips = 10; mult = 1; break;

        case HandRank::TwoPair:
            chips = 20; mult = 2; break;

        case HandRank::ThreeOfAKind:
            chips = 30; mult = 2; break;

        case HandRank::Straight:
            chips = 40; mult = 3; break;

        case HandRank::Flush:
            chips = 50; mult = 3; break;

        case HandRank::FullHouse:
            chips = 70; mult = 4; break;

        case HandRank::FourOfAKind:
            chips = 100; mult = 5; break;

        case HandRank::StraightFlush:
            chips = 150; mult = 8; break;
    }

    return { chips, mult, chips * mult };
}