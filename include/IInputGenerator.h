#pragma once
#include "TurnInput.h"

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate() = 0;
};
