#include <iostream>
#include "RunSession.h"
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "ModifierFactory.h"

int main() {
    std::cout << "=== Balatro, Chemistry? ===" << std::endl;

    ScoringSystem scoring;
    ShopSystem shop;
    ModifierFactory factory;

    RunSession session(&scoring, &shop, &factory);
    session.start();

    return 0;
}