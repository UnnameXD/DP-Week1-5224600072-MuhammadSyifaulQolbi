#include "BonusRewardRule.h"

int BonusRewardRule::compute(int baseScore, int roundNumber) {
    if (roundNumber % 2 == 0) {
        return baseScore * 2;   // even round: double
    } else {
        return baseScore + 2;   // odd round:  +2 bonus
    }
}
