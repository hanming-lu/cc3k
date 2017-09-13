// Complete
#include "Troll.h"
#include "PC.h"

//provides maxHP
int Troll::getMaxHP() {
    return maxHP;
}

Type Troll::getType() const {
    // return the most detailed type
    return Type::Troll;
}

// calls PC's ctor
Troll::Troll(int x, int y) : PC(120, 25, 15, x, y) {}
