#pragma once
#include "IInputGenerator.h"

class SequentialInputGenerator : public IInputGenerator {
public:
    SequentialInputGenerator();
    TurnInput generate() override;

private:
    int _index;
    static const int SEQUENCE[];
    static const int SEQUENCE_SIZE;
};
