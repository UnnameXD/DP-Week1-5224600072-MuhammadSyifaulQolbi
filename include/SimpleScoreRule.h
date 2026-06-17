#pragma once
#include "IScoringRule.h"

class SimpleScoreRule : public IScoringRule {
public:
    int compute(const TurnInput& input) override;
};
