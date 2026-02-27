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