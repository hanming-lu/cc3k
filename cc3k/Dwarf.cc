// Complete
#include "Dwarf.h"

Type Dwarf::getType() const {
    // returns the most detailed Type
    return Type::Dwarf;
}

// ctor calls Enemy's ctor
Dwarf::Dwarf(int x, int y) : Enemy(100, 20, 30, x, y) {}
