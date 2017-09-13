// Complete
#include "SuperMan.h"

Type SuperMan::getType() const {
    // return the most detailed type
    return Type::SuperMan;
}

//provides maxHP
int SuperMan::getMaxHP() {
    return maxHP;
}

// Superman is super strong
SuperMan::SuperMan(int x, int y) : PC(99999, 99, 99, x, y) {}
