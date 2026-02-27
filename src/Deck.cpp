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

    std::vector<std::string> nonLogam = {
        "Hidrogen","Karbon","Nitrogen","Oksigen","Fosfor",
        "Flourin","Klorin","Bromin","Iodin","Astatin",
        "Assistant","Marie Curie","Mendeleev"
    };

    std::vector<std::string> alkali = {
        "Litium","Natrium","Kalium","Rubidium","Sesium",
        "Fransium","Magnesium","Kalsium","Stronsium","Barium",
        "Assistant","Marie Curie","Mendeleev"
    };

    std::vector<std::string> transisi = {
        "Skandium","Besi","Nikel","Tembaga","Seng",
        "Perak","Platinum","Emas","Merkuri","Tungsten",
        "Assistant","Marie Curie","Mendeleev"
    };

    std::vector<std::string> gasMuliaAndNuklir = {
        "Helium","Neon","Argon","Kripton","Xenon",
        "Radon","Uranium","Plutonium","Thorium","Curium",
        "Assistant","Marie Curie","Mendeleev"
    };

    addSuit(Suit::NonLogam, nonLogam);
    addSuit(Suit::Alkali, alkali);
    addSuit(Suit::Transisi, transisi);
    addSuit(Suit::GasMulia, gasMuliaAndNuklir);
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