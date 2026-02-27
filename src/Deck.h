#pragma once
#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();

    void shuffle();
    Card drawCard();
    bool isEmpty() const;

private:
    std::vector<Card> cards;

    void initializeDeck();
    void addSuit(Suit suit, const std::vector<std::string>& elements);
};