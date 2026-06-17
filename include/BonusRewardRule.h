#pragma once
#include "IRewardRule.h"

// Modification 2: reward != base score
// Odd rounds:  reward = baseScore + 2
// Even rounds: reward = baseScore * 2
class BonusRewardRule : public IRewardRule {
public:
    int compute(int baseScore, int roundNumber) override;
};
