// test mode
#include <iostream>
#include "Deck.h"


int main() {
    std::cout << "=== Deck Test ===" << std::endl;

    Deck deck;

    deck.shuffle();

    std::cout << "Drawing 5 cards:\n";

    for (int i = 0; i < 5; i++) {
        Card card = deck.drawCard();

        std::cout 
            << "Rank: " << card.getRank()
            << " | Element: " << card.getSymbol()
            << std::endl;
    }

    return 0;
}