// Complete
#include "Shade.h"

//provides maxHP
int Shade::getMaxHP() {
    return maxHP;
}

// return the most detailed type
Type Shade::getType() const {
    return Type::Shade;
}

// calls PC's ctor
Shade::Shade(int x, int y) : PC(125, 25, 25, x, y) {}
