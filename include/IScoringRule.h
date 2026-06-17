#pragma once
#include "TurnInput.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int compute(const TurnInput& input) = 0;
};
