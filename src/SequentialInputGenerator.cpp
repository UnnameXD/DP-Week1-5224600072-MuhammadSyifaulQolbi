#include "SequentialInputGenerator.h"

const int SequentialInputGenerator::SEQUENCE[]    = {3, 5, 7};
const int SequentialInputGenerator::SEQUENCE_SIZE = 3;

SequentialInputGenerator::SequentialInputGenerator() : _index(0) {}

TurnInput SequentialInputGenerator::generate() {
    int value = SEQUENCE[_index % SEQUENCE_SIZE];
    _index++;
    return TurnInput(value);
}
