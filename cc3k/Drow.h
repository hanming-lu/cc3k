// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Drow_hpp
#define Drow_hpp
#include "PC.h"
#include "Type.h"

class Drow final : public PC {
    const int maxHP = 150;
public:
    Type getType() const override; // return the most detailed type
    virtual int getMaxHP() override; //provides maxHP
    virtual int getAtkVal() override; // return the 1.5 x after potion Atk value
    virtual int getDefVal() override; // return the 1.5 x after potion Def value
    
    Drow(int x, int y); // calls PC's ctor
};

#endif 
