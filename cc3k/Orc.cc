// Complete
#include "Orc.h"

Type Orc::getType() const {
    // returns the most detailed Type
    return Type::Orc;
}

// ctor calls Enemy's ctor
Orc::Orc(int x, int y) : Enemy(180, 30, 25, x, y) {}
