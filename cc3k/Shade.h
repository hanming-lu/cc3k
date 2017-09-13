// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Shade_h
#define Shade_h
#include "PC.h"
#include "Type.h"

class Shade final : public PC {
    const int maxHP = 125;
public:
    virtual int getMaxHP() override; //provides maxHP
    Type getType() const override; // return the most detailed type
    
    Shade(int x, int y); // calls PC's ctor
};

#endif
