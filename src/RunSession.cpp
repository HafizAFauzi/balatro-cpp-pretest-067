#include "RunSession.h"
#include "HandEvaluator.h"
#include "BlindFactory.h"
#include <iostream>
#include <algorithm>
#include <limits>

RunSession::RunSession(int ante)
    : currentBlind(BlindFactory::createSmallBlind(ante)),
      totalScore(0),
      handsRemaining(4),
      discardsRemaining(3),
      currentAnte(ante),
      coins(0)
{
}

void RunSession::start() {
    std::cout << "=== Poker, Reaction? ===\n";
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
    discardsRemaining = 3;

    drawUpToEight();

    while (handsRemaining > 0 &&
           totalScore < currentBlind.getTargetScore()) {

        std::cout << "\n=========================\n";
        std::cout << "Total Score: " << totalScore
                  << " | Hands Left: " << handsRemaining
                  << " | Discards Left: " << discardsRemaining
                  << " | Coins: " << coins
                  << "\n\n";

        showCurrentHand();

        std::cout << "Choose action: (1) Play Hand  (2) Discard : ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 2) {
            discardCards();
            continue;
        }

        // ==== PLAY HAND ====
        std::vector<int> chosenIndices = getPlayerChoice();

        if (chosenIndices.empty()) {
            std::cout << "You must choose at least 1 card.\n";
            continue;
        }

        std::vector<Card> playedCards;
        for (int index : chosenIndices) {
            playedCards.push_back(currentHand[index]);
        }

        HandRank rank = HandEvaluator::evaluate(playedCards);
        ScoreResult result = scoringSystem.calculateScore(rank);

        // APPLY MODIFIERS
        for (auto& mod : modifiers)
        {
            mod->apply(result, rank);
        }

        totalScore += result.total;

        std::cout << "Hand Score: " << result.total << "\n";

        removePlayedCards(chosenIndices);
        drawUpToEight();

        handsRemaining--;
    }

    if (totalScore >= currentBlind.getTargetScore()) {
        // std::cout << "Blind Cleared! Sisa skor akan dikonversi (opsional).\n";
        int reward = handsRemaining;

        coins += reward;
        coins += 7;

        std::cout << "Blind Cleared!\n";
        std::cout << "Reward Coins: 7\n";
        std::cout << "Coins from remaining hands: "
                  << reward << "\n";

        std::cout << "Total Coins: " << coins << "\n";

        shop.openShop(coins, *this);

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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return indices;
}

void RunSession::removePlayedCards(const std::vector<int>& indices) {

    for (int i = indices.size() - 1; i >= 0; i--) {
        currentHand.erase(currentHand.begin() + indices[i]);
    }
}

void RunSession::discardCards() {

    if (discardsRemaining <= 0) {
        std::cout << "No discards remaining!\n";
        return;
    }

    std::cout << "Enter card indices to discard (end with -1): ";

    std::vector<int> indices;
    while (true) {
        int idx;
        if (!(std::cin >> idx)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (idx == -1) break;

        if (idx >= 0 && idx < (int)currentHand.size()) {

            // Cegah pilih index sama dua kali
            if (std::find(indices.begin(), indices.end(), idx) == indices.end()) {
                indices.push_back(idx);
            }
        }
    }

    if (indices.empty()) {
        std::cout << "No cards discarded.\n";
        return;
    }

    std::sort(indices.begin(), indices.end());

    for (int i = indices.size() - 1; i >= 0; i--) {
        currentHand.erase(currentHand.begin() + indices[i]);
    }

    discardsRemaining--;
    drawUpToEight();

    std::cout << "Cards discarded. Discards left: "
              << discardsRemaining << "\n";
}

void RunSession::addModifier(std::unique_ptr<Modifier> mod)
{
    modifiers.push_back(std::move(mod));
}