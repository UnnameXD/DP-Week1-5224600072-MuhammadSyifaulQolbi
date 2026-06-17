#include "RunSession.h"
#include "SequentialInputGenerator.h"
#include "RandomInputGenerator.h"
#include "SimpleScoreRule.h"
#include "SimpleRewardRule.h"
#include "BonusRewardRule.h"
#include "ShopSystem.h"

int main() {
    // === Modification 1: swap input generator here (NOT inside RunSession) ===
    // SequentialInputGenerator inputGen;   // original
    RandomInputGenerator inputGen;          // modified

    // === Modification 2: swap reward rule here (NOT inside RunSession) ===
    // SimpleRewardRule rewardRule;         // original: reward = baseScore
    BonusRewardRule rewardRule;             // modified: odd=+2, even=*2

    SimpleScoreRule scoringRule;
    ShopSystem      shopSystem;

    RunSession session(&inputGen, &scoringRule, &rewardRule, &shopSystem, 3);
    session.run();

    return 0;
}
