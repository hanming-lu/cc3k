// Complete
#include "Drow.h"

// return the most detailed type
Type Drow::getType() const {
    return Type::Drow;
}

// return the maxHP
int Drow::getMaxHP() {
    return maxHP;
}

int Drow::getAtkVal() {
    // return the after potion Atk value
    int tmp = this->Atk + tmpPotions[Type::BA] * 7 - tmpPotions[Type::WA] * 7;
    if (tmp < 0) return 0;
    return tmp;
}

int Drow::getDefVal() {
    // return the after potion Def value
    int tmp = this->Def + tmpPotions[Type::BD] * 7 - tmpPotions[Type::WD] * 7;
    if (tmp < 0) return 0;
    return tmp;
}

// calls PC's ctor
Drow::Drow(int x, int y) : PC(150, 25, 15, x, y) {}
