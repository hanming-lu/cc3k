// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef PC_h
#define PC_h
#include <map>
#include "Character.h"
#include "Type.h"
#include "LowerGenre.h"
class Enemy;

class PC : public Character {
protected:
    int gold = 0;
    int pregold = 0;
    int prepregold = 0;
    std::map<Type, int> tmpPotions;

public:
    virtual int modHP(int modVal) override; // modify current HP by modVal, return the modified HP, won't exceed maxHP, if 0, the Character is slain
    virtual int getMaxHP() = 0; // gets the maxHP of the PC
    virtual void modGold(int modVal); // modify the gold by modVal amount
    virtual int getGold(); // get the gold
    virtual int getPreGold(); // get the Pregold
    virtual int getPrePreGold(); // get the Pregold
    virtual void rmEffect(); // remove PC's effect
    virtual void attack(Enemy &victim) ; // calls victim's beAttacked, check if victim is dead
    virtual void beAttacked(Enemy &attacker) ; // DO NOT call this method dirrectly. attack(PC &) will call this method
    virtual int getAtkVal() override; // return the after potion Atk value
    virtual int getDefVal() override; // return the after potion Def value
    void usePotion(Type thePotion); // add thePotion to the tmpPotions array

    LowerGenre getLowerGenre() const override; // return lower genre
    
    PC(int HP, int Atk, int Def, int x, int y); // calls Character's ctor
    virtual ~PC() = 0;
    
};



#endif
