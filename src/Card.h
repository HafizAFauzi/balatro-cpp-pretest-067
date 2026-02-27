#pragma once
#include <string>

enum class Suit {
    NonLogam,     // Hati
    Alkali,       // Sekop
    Transisi,     // Keriting
    GasMulia      // Wajik
};

class Card {
public:
    Card(Suit suit, int rank, const std::string& symbol);

    int getRank() const;
    Suit getSuit() const;
    std::string getSymbol() const;

private:
    Suit suit;
    int rank;              // 1-13 (A-K)
    std::string symbol;    // "H", "Li", "Fe"
};