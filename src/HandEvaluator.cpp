#include "HandEvaluator.h"
#include <algorithm>
#include <map>
#include <stdexcept>

HandRank HandEvaluator::evaluate(const std::vector<Card>& hand) {

    if (hand.size() != 5) {
        throw std::runtime_error("Hand must contain exactly 5 cards");
    }

    // Ambil rank poker (Ace = 14)
    std::vector<int> values;
    for (const auto& card : hand) {
        values.push_back(card.getPokerValue());
    }

    std::sort(values.begin(), values.end());

    // Hitung frekuensi rank
    std::map<int, int> freq;
    for (int v : values) {
        freq[v]++;
    }

    std::vector<int> counts;

    for (const auto& pair : freq) {
        counts.push_back(pair.second);
    }

    std::sort(counts.begin(), counts.end(), std::greater<int>());

    // ===== Cek Straight =====
    bool isStraight = true;

    // Cek tidak ada duplikat
    if (freq.size() != 5) {
        isStraight = false;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (values[i] + 1 != values[i + 1]) {
                isStraight = false;
                break;
            }
        }
    }

    // Special case: A 2 3 4 5
    if (!isStraight) {
        if (values == std::vector<int>{2,3,4,5,14}) {
            isStraight = true;
        }
    }

    // ===== Cek Flush =====
    bool isFlush = true;
    Suit firstSuit = hand[0].getSuit();

    for (const auto& card : hand) {
        if (card.getSuit() != firstSuit) {
            isFlush = false;
            break;
        }
    }

    // ===== Straight Flush =====
    if (isStraight && isFlush)
    return HandRank::StraightFlush;
    
    // ===== Four of a Kind =====
    if (counts[0] == 4)
        return HandRank::FourOfAKind;

    // ===== Full House =====
    if (counts[0] == 3 && counts[1] == 2)
        return HandRank::FullHouse;

    // ===== Flush =====
    if (isFlush)
        return HandRank::Flush;

    // ===== Straight =====
    if (isStraight)
        return HandRank::Straight;

    // ===== Three of a Kind =====
    if (counts[0] == 3)
        return HandRank::ThreeOfAKind;

    // ===== Two Pair =====
    if (counts[0] == 2 && counts[1] == 2)
        return HandRank::TwoPair;

    // ===== One Pair =====
    if (counts[0] == 2)
        return HandRank::OnePair;


    // ===== Nanti logic masuk sini =====
    

    return HandRank::HighCard;
}