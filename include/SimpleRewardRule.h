#pragma once
#include "IRewardRule.h"

class SimpleRewardRule : public IRewardRule {
public:
    int compute(int baseScore, int roundNumber) override;
};
