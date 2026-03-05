#pragma once

#include <vector>
#include "Deck.h"
#include "Blind.h"
#include "ScoringSystem.h"
#include "Card.h"
#include "ShopSystem.h"
#include "modifiers/IModifier.h"
#include <memory>


class RunSession {
public:
    RunSession(int ante);
    void addModifier(std::unique_ptr<Modifier> mod);
    void start();

private:
    bool playBlind(const Blind& blind);
    void drawUpToEight();
    void showCurrentHand() const;
    std::vector<int> getPlayerChoice() const;
    void removePlayedCards(const std::vector<int>& indices); 
    void discardCards();

    Deck deck;
    Blind currentBlind;
    ScoringSystem scoringSystem;
    ShopSystem shop;

    std::vector<Card> currentHand;
    std::vector<std::unique_ptr<Modifier>> modifiers;

    int totalScore;
    int handsRemaining;
    int discardsRemaining; 
    int currentAnte;
    int coins;
};