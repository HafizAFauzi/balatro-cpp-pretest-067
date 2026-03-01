#include "RunSession.h"
#include "HandEvaluator.h"
#include "BlindFactory.h"
#include <iostream>
#include <algorithm>

RunSession::RunSession(int ante)
    : currentBlind(BlindFactory::createSmallBlind(ante)),
      totalScore(0),
      handsRemaining(4)
{
}

void RunSession::start() {

    std::cout << "=== Starting Run ===\n";
    std::cout << "Blind: " << currentBlind.getName()
              << " | Target: "
              << currentBlind.getTargetScore()
              << "\n\n";

    deck = Deck();
    deck.shuffle();

    totalScore = 0;
    handsRemaining = 4;
    currentHand.clear();

    playBlind();
}

void RunSession::playBlind() {

    drawUpToEight();

    while (handsRemaining > 0 &&
           totalScore < currentBlind.getTargetScore()) {

        std::cout << "\n=========================\n";
        std::cout << "Total Score: " << totalScore
                  << " | Hands Left: " << handsRemaining
                  << "\n\n";

        showCurrentHand();

        std::vector<int> chosenIndices = getPlayerChoice();

        std::vector<Card> playedCards;
        for (int index : chosenIndices) {
            playedCards.push_back(currentHand[index]);
        }

        HandRank rank = HandEvaluator::evaluate(playedCards);
        ScoreResult result = scoringSystem.calculateScore(rank);

        totalScore += result.total;

        std::cout << "Hand Score: " << result.total << "\n";

        removePlayedCards(chosenIndices);
        drawUpToEight();

        handsRemaining--;
    }

    if (totalScore >= currentBlind.getTargetScore()) {
        std::cout << "\nBlind Cleared!\n";
    } else {
        std::cout << "\nFailed to reach target.\n";
    }
}

void RunSession::drawUpToEight() {
    while (currentHand.size() < 8 && !deck.isEmpty()) {
        currentHand.push_back(deck.drawCard());
    }

    // SORT DESCENDING (besar → kecil)
    std::sort(currentHand.begin(), currentHand.end(),
        [](const Card& a, const Card& b) {
            return a.getPokerValue() > b.getPokerValue();
        });
}

void RunSession::showCurrentHand() const {
    std::cout << "Your Hand:\n";

    for (size_t i = 0; i < currentHand.size(); ++i) {
        std::cout << i << ": "
                  << currentHand[i].getRankString()
                  << currentHand[i].getSymbol()
                  << "\n";
    }

    std::cout << "\n";
}

std::vector<int> RunSession::getPlayerChoice() const {
    std::vector<int> indices;
    std::cout << "Enter card indices (1-5 cards, end with -1): ";

    while (indices.size() < 5) {
        int idx;
        if (!(std::cin >> idx)) { // Jika user input huruf, bersihkan buffer
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (idx == -1) break;

        // Validasi: Indeks harus dalam range tangan DAN belum pernah dipilih sebelumnya
        if (idx >= 0 && idx < (int)currentHand.size()) {
            bool alreadyChosen = false;
            for (int existing : indices) {
                if (existing == idx) {
                    alreadyChosen = true;
                    break;
                }
            }

            if (!alreadyChosen) {
                indices.push_back(idx);
            } else {
                std::cout << "Indeks " << idx << " sudah dipilih!\n";
            }
        }
    }

    // Paksa user pilih minimal 1 kartu seperti di Balatro
    if (indices.empty()) {
        std::cout << "Kamu harus memilih minimal 1 kartu untuk dimainkan!\n";
        return getPlayerChoice(); // Minta ulang
    }

    // Tetap sort agar removePlayedCards menghapus dari belakang ke depan dengan benar
    std::sort(indices.begin(), indices.end());
    return indices;
}

void RunSession::removePlayedCards(const std::vector<int>& indices) {

    for (int i = indices.size() - 1; i >= 0; i--) {
        currentHand.erase(currentHand.begin() + indices[i]);
    }
}