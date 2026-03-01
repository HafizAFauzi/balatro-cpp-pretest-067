#pragma once
#include "Blind.h"

class BlindFactory {
public:
    static Blind createSmallBlind(int ante);
    static Blind createBigBlind(int ante);
};