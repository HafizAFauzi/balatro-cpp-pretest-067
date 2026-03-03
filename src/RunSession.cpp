#include "RunSession.h"
#include "HandEvaluator.h"
#include "BlindFactory.h"
#include <iostream>
#include <algorithm>

RunSession::RunSession(int ante)
    : currentBlind(BlindFactory::createSmallBlind(ante)),
      totalScore(0),
      handsRemaining(4),
      currentAnte(ante)
{
}

void RunSession::start() {
    std::cout << "=== Starting Run (Ante " << currentAnte << ") ===\n";

    // 1. Jalankan Small Blind
    if (!playBlind(BlindFactory::createSmallBlind(currentAnte))) {
        std::cout << "GAME OVER di Small Blind.\n";
        return;
    }

    // 2. Jalankan Big Blind
    if (!playBlind(BlindFactory::createBigBlind(currentAnte))) {
        std::cout << "GAME OVER di Big Blind.\n";
        return;
    }

    // 3. Jalankan Boss Blind
    // (Pastikan kamu sudah menambah createBossBlind di BlindFactory)
    if (!playBlind(BlindFactory::createBossBlind(currentAnte))) {
        std::cout << "GAME OVER di Boss Blind.\n";
        return;
    }

    std::cout << "\nCONGRATULATIONS! Kamu menyelesaikan Ante " << currentAnte << "!\n";
}

// Berikan return bool untuk mengecek apakah pemain menang atau kalah
bool RunSession::playBlind(const Blind& blind) {
    currentBlind = blind; // Set blind aktif saat ini
    
    std::cout << "\n--- NEW BLIND: " << currentBlind.getName() 
              << " (Target: " << currentBlind.getTargetScore() << ") ---\n";

    // Reset status untuk setiap blind baru
    deck = Deck();
    deck.shuffle();
    currentHand.clear();
    totalScore = 0;
    handsRemaining = 4;

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
        // std::cout << "Blind Cleared! Sisa skor akan dikonversi (opsional).\n";
        return true; // Berhasil lanjut
    } else {
        return false; // Kalah
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
                  << currentHand[i].getRankString() << " "
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