#include "HandEvaluator.h"
#include <algorithm>
#include <map>
#include <stdexcept>

HandRank HandEvaluator::evaluate(const std::vector<Card>& hand) {
    // 1. UBAH VALIDASI: Izinkan 1 sampai 5 kartu
    if (hand.empty() || hand.size() > 5) {
        throw std::runtime_error("Hand must contain between 1 and 5 cards");
    }

    int handSize = (int)hand.size();

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

    // ===== 2. LOGIKA STRAIGHT (Hanya mungkin jika ada 5 kartu) =====
    bool isStraight = false;
    if (handSize == 5) {
        isStraight = true;
        if (freq.size() != 5) {
            isStraight = false;
        } else {
            for (int i = 0; i < 4; i++) {
                if (values[i] + 1 != values[i + 1]) {
                    isStraight = false;
                    break;
                }
            }
        }
        // Special case: A 2 3 4 5
        if (!isStraight && values == std::vector<int>{2, 3, 4, 5, 14}) {
            isStraight = true;
        }
    }

    // ===== 3. LOGIKA FLUSH (Hanya mungkin jika ada 5 kartu) =====
    bool isFlush = false;
    if (handSize == 5) {
        isFlush = true;
        Suit firstSuit = hand[0].getSuit();
        for (const auto& card : hand) {
            if (card.getSuit() != firstSuit) {
                isFlush = false;
                break;
            }
        }
    }

    // ===== 4. EVALUASI RANK (Urutan Balatro) =====
    
    // Straight Flush
    if (isStraight && isFlush) return HandRank::StraightFlush;
    
    // Four of a Kind (Bisa dideteksi dari 4 atau 5 kartu)
    if (counts[0] == 4) return HandRank::FourOfAKind;

    // Full House (Hanya mungkin dengan 5 kartu: 3 + 2)
    if (handSize == 5 && counts[0] == 3 && counts[1] == 2) return HandRank::FullHouse;

    // Flush
    if (isFlush) return HandRank::Flush;

    // Straight
    if (isStraight) return HandRank::Straight;

    // Three of a Kind (Bisa dari 3, 4, atau 5 kartu)
    if (counts[0] == 3) return HandRank::ThreeOfAKind;

    // Two Pair (Bisa dari 4 atau 5 kartu)
    if (counts.size() >= 2 && counts[0] == 2 && counts[1] == 2) return HandRank::TwoPair;

    // One Pair (Bisa dari 2, 3, 4, atau 5 kartu)
    if (counts[0] == 2) return HandRank::OnePair;

    // High Card
    return HandRank::HighCard;
}