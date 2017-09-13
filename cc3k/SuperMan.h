// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef SuperMan_h
#define SuperMan_h
#include "PC.h"
#include "Type.h"

class SuperMan final : public PC {
    int maxHP = 99999;
public:
    Type getType() const override; // return the most detailed type
    virtual int getMaxHP() override; //provides maxHP
    
    SuperMan(int x, int y); // calls PC's ctor
};

#endif
