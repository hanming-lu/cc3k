// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Character_h
#define Character_h
#include <iostream>
#include <string>
#include "Base.h"

class Character : public Base {
protected:
    int HP; // current HP
    int preHP; // previous HP
    int Atk; // Base Atk value
    int Def; // Base Def value

public:
    virtual int modHP(int modVal); // modify current HP by modVal, return the modified HP, if 0, the Character is slain
    int getHPVal();
    int getPreHPVal();
    virtual int getAtkVal();
    virtual int getDefVal();
    bool isDead(); // return true if Character is dead
    
    Character(int HP, int Atk, int Def, int x, int y); // calls Base's ctor
    virtual ~Character() = 0;
};

#endif
