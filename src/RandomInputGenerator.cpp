#include "RandomInputGenerator.h"
#include <cstdlib>
#include <ctime>

RandomInputGenerator::RandomInputGenerator() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

TurnInput RandomInputGenerator::generate() {
    int value = (std::rand() % 10) + 1; // 1..10
    return TurnInput(value);
}
