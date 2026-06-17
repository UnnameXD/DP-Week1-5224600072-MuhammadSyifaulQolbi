#pragma once
#include "IInputGenerator.h"

// Modification 1: replacement input generator
// Generates random values between 1 and 10
class RandomInputGenerator : public IInputGenerator {
public:
    RandomInputGenerator();
    TurnInput generate() override;
};
