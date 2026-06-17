#include "RunSession.h"
#include <iostream>

RunSession::RunSession(
    IInputGenerator* inputGenerator,
    IScoringRule*    scoringRule,
    IRewardRule*     rewardRule,
    ShopSystem*      shopSystem,
    int              rounds
)
    : _inputGenerator(inputGenerator)
    , _scoringRule(scoringRule)
    , _rewardRule(rewardRule)
    , _shopSystem(shopSystem)
    , _rounds(rounds)
    , _money(0)
{}

void RunSession::run() {
    std::cout << "=== RUN START ===\n\n";

    for (int round = 1; round <= _rounds; ++round) {
        std::cout << "Round " << round << "\n";

        // Phase 1: Generate input
        TurnInput input = _inputGenerator->generate();
        std::cout << "[PLAY]   input generated: " << input.value << "\n";

        // Phase 2: Compute base score
        int baseScore = _scoringRule->compute(input);
        std::cout << "[SCORE]  base score: " << baseScore << "\n";

        // Phase 3 & 4: Compute reward and update money
        int reward = _rewardRule->compute(baseScore, round);
        _money += reward;
        std::cout << "[REWARD] gain: " << reward << " | money: " << _money << "\n";

        // Phase 5: Shop phase
        _shopSystem->offer(_money);

        // Phase 6: Advance round (loop continues)
        std::cout << "\n";
    }

    std::cout << "=== RUN END ===\n";
    std::cout << "Final money: " << _money << "\n";
}
