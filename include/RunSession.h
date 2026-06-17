#pragma once
#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

// Controls the INVARIANT game loop.
// Must NOT contain scoring, reward, or input generation logic.
class RunSession {
public:
    RunSession(
        IInputGenerator* inputGenerator,
        IScoringRule*    scoringRule,
        IRewardRule*     rewardRule,
        ShopSystem*      shopSystem,
        int              rounds = 3
    );

    void run();

private:
    IInputGenerator* _inputGenerator;
    IScoringRule*    _scoringRule;
    IRewardRule*     _rewardRule;
    ShopSystem*      _shopSystem;
    int              _rounds;
    int              _money;
};
