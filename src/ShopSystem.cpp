#include "ShopSystem.h"
#include "RunSession.h"
#include "modifiers/PairBooster.h"
#include "modifiers/DoubleScore.h"
#include <iostream>
#include <cstdlib>
#include <limits>

void ShopSystem::openShop(int& coins, RunSession& runSession)
{
    std::cout << "\n===== SHOP =====\n";
    std::cout << "Coins: " << coins << "\n";

    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << i+1 << ". "
                  << items[i].name
                  << " (Cost: " << items[i].cost << ")\n";
    }

    std::cout << "0. Leave shop\n";

    int choice;
    std::cin >> choice;

    if (choice == 0)
    {
        std::cout << "Leaving shop...\n";
        return;
    }

    if (choice < 1 || choice > items.size())
    {
        std::cout << "Invalid choice\n";
        return;
    }

    ShopItem item = items[choice-1];

    if (coins < item.cost)
    {
        std::cout << "Not enough coins!\n";
        return;
    }

    coins -= item.cost;

    std::cout << item.name << " purchased!\n";

    // ===== TAMBAHKAN MODIFIER =====
    if(item.name == "Pair Booster")
    {
        runSession.addModifier(std::make_unique<PairBooster>());
    }

    if(item.name == "Double Score")
    {
        runSession.addModifier(std::make_unique<DoubleScore>());
    }
}