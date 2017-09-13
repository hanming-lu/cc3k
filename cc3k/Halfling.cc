// Complete
#include "Halfling.h"

Type Halfling::getType() const {
    // returns the most detailed Type
    return Type::Halfling;
}

// ctor calls Enemy's ctor
Halfling::Halfling(int x, int y) : Enemy(100, 15, 20, x, y) {}
