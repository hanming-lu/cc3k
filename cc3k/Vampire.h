// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Vampire_h
#define Vampire_h
#include "Type.h"
#include "PC.h"
class Enemy;

class Vampire final : public PC {
public:
    Type getType() const override; // return the most detailed type
    int modHP(int modVal) override; // no maxHP limit
    virtual int getMaxHP() override; //provides maxHP
    void attack(Enemy &victim) override; // check if victim is Dwarf, if yes, then calls modHP(-5), if not, calls modHP(5)
    
    Vampire(int x, int y); // calls PC's ctor
};
#endif
