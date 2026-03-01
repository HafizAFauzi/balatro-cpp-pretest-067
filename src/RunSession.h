#pragma once

#include <vector>
#include "Deck.h"
#include "Blind.h"
#include "ScoringSystem.h"
#include "Card.h"

class RunSession {
public:
    RunSession(int ante);
    void start();

private:
    void playBlind();
    void drawUpToEight();
    void showCurrentHand() const;
    std::vector<int> getPlayerChoice() const;
    void removePlayedCards(const std::vector<int>& indices);

    Deck deck;
    Blind currentBlind;
    ScoringSystem scoringSystem;

    std::vector<Card> currentHand;

    int totalScore;
    int handsRemaining;
};