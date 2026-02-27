#pragma once

#include <vector>
#include <memory>

// Forward declaration (biar tidak circular include)
class ScoringSystem;
class ShopSystem;
class ModifierFactory;
class IModifier;

class RunSession {
public:
    // Constructor (Dependency Injection)
    RunSession(ScoringSystem* scoring,
               ShopSystem* shop,
               ModifierFactory* factory);

    // Mulai game loop
    void start();

private:
    // Core loop
    void playRound();
    void handleShopPhase();
    void applyModifiers(int& score);

    // Game state
    int currentRound;
    int totalScore;
    bool isRunning;

    // Systems
    ScoringSystem* scoringSystem;
    ShopSystem* shopSystem;
    ModifierFactory* modifierFactory;

    // Active modifiers
    std::vector<std::shared_ptr<IModifier>> activeModifiers;
};