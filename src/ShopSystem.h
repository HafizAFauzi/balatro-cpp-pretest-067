#pragma once
#include <vector>
#include <string>

class RunSession;

struct ShopItem {
    std::string name;
    int cost;
};

class ShopSystem {
public:
    void openShop(int& coins, RunSession& runSession);

private:
    std::vector<ShopItem> items = {
            {"Double Score", 6},
            {"Pair Booster", 5}
    };
};