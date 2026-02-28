#include "Card.h"

Card::Card(Suit suit, int rank, const std::string& symbol)
    : suit(suit), rank(rank), symbol(symbol) {}

int Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}

std::string Card::getSymbol() const {
    return symbol;
}

int Card::getPokerValue() const {
    if (rank == 1) return 14;  // Ace tertinggi
    return rank;
}

std::string Card::getRankString() const {
    switch(rank) {
        case 1:  return "A";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: return std::to_string(rank);
    }
}