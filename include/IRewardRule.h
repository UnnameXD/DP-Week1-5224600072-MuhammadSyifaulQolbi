#pragma once

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int compute(int baseScore, int roundNumber) = 0;
};
