// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Goblin_h
#define Goblin_h
#include "PC.h"
#include "Type.h"
class Enemy;

class Goblin final : public PC {
    const int maxHP = 125;
public:
    Type getType() const override; // return the most detailed type
    void attack(Enemy &victim) override; // calls enemy's beAttack, if return value is true, modGold(5)
    void beAttacked(Enemy &attacker) override; // if attacker is orcs, then does 50% more dmg
    virtual int getMaxHP() override; //provides maxHP

    
    Goblin(int x, int y); // calls PC's ctor
};

#endif
