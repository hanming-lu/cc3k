// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Troll_h
#define Troll_h
#include "PC.h"
#include "Type.h"

class Troll final : public PC {
    const int maxHP = 120;
public:
    virtual int getMaxHP() override; //provides maxHP
    Type getType() const override; // return the most detailed type
    
    Troll(int x, int y); // calls PC's ctor
};

#endif
