// Complete
#include <stdlib.h>
#include <time.h>
#include "Elf.h"
#include "PC.h"

Type Elf::getType() const {
    // returns the most detailed Type
    return Type::Elf;
}

// ctor calls Enemy's ctor
Elf::Elf(int x, int y) : Enemy(140, 30, 10, x, y) {}
