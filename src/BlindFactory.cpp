#include "BlindFactory.h"

Blind BlindFactory::createSmallBlind(int ante) {
    int target = 100 * ante;
    return Blind("Small Blind", target);
}

Blind BlindFactory::createBigBlind(int ante) {
    int target = 200 * ante;
    return Blind("Big Blind", target);
}

Blind BlindFactory::createBossBlind(int ante) {
    int target = 400 * ante; 
    return Blind("Boss Blind", target);
}