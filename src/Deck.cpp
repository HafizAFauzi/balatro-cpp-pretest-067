#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>

Deck::Deck() {
    initializeDeck();
}

// ===== Implementasi initializeDeck =====
void Deck::initializeDeck() {
    cards.clear();

    std::vector<std::string> pyro = {
        "Pyro","Pyro","Pyro","Pyro","Pyro",
        "Pyro","Pyro","Pyro","Pyro","Pyro",
        "Diluc (Pyro)","Mavuika (Pyro)","Haborym (Pyro)"
    };

    std::vector<std::string> hydro = {
        "Hydro","Hydro","Hydro","Hydro","Hydro",
        "Hydro","Hydro","Hydro","Hydro","Hydro",
        "Barbara (Hydro)","Furina (Hydro)","Focalors (Hydro)"
    };

    std::vector<std::string> cryo = {
        "Cryo","Cryo","Cryo","Cryo","Cryo",
        "Cryo","Cryo","Cryo","Cryo","Cryo",
        "Eula (Cryo)","La Signora (Cryo)","Tsaritsa (Cryo)"
    };

    std::vector<std::string> electro = {
        "Electro","Electro","Electro","Electro","Electro",
        "Electro","Electro","Electro","Electro","Electro",
        "Raiden Shogun (Electro)","Ei (Electro)","Beelzebul (Electro)"
    };

    addSuit(Suit::Pyro, pyro);
    addSuit(Suit::Hydro, hydro);
    addSuit(Suit::Cryo, cryo);
    addSuit(Suit::Electro, electro);
}

// ===== Implementasi addSuit =====
void Deck::addSuit(Suit suit, const std::vector<std::string>& elements) {
    for (int i = 0; i < elements.size(); i++) {
        cards.emplace_back(suit, i + 1, elements[i]);
    }
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(),
                 std::default_random_engine(std::time(nullptr)));
}

Card Deck::drawCard() {
    if (cards.empty()) {
        throw std::runtime_error("Deck is empty!");
    }

    Card top = cards.back();
    cards.pop_back();
    return top;
}

bool Deck::isEmpty() const {
    return cards.empty();
}