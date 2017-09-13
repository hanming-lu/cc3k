// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Dwarf_h
#define Dwarf_h
#include "Enemy.h"
#include "Type.h"

class Dwarf final : public Enemy {
public:
    Type getType() const override; // returns the most detailed Type

    Dwarf(int x, int y); // calls Enemy's ctor
};

#endif
