// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Elf_h
#define Elf_h
#include "Enemy.h"
#include "Type.h"

class Elf final : public Enemy {
public:
    Type getType() const override; // returns the most detailed Type

    Elf(int x, int y); // calls Enemy's ctor
};

#endif
