#include "ShopSystem.h"
#include <iostream>

void ShopSystem::offer(int currentMoney) {
    const char* itemName = "Bonus(+2)";
    const int   itemCost = 2;

    std::cout << "[SHOP]   offered: " << itemName << " cost " << itemCost << "\n";
    if (currentMoney >= itemCost) {
        std::cout << "[SHOP]   skipped (can afford, but chose to save)\n";
    } else {
        std::cout << "[SHOP]   skipped (not enough money)\n";
    }
}
