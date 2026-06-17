#include "SimpleScoreRule.h"

int SimpleScoreRule::compute(const TurnInput& input) {
    return input.value;
}
