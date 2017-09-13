// Complete
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Goblin.h"
#include "Enemy.h"

// return the most detailed type
Type Goblin::getType() const {
    return Type::Goblin;
}
void Goblin::attack(Enemy &victim) {
    // track if the victim is halfling, if yes, then 50% chance to miss
    int validAttack = 1;
    if (victim.getType() == Type::Halfling) {
        validAttack = rand() % 2;
    }
    // if attack is valid, then call beAttacked on the victim
    if (validAttack) {
        victim.beAttacked(*this);
        
        // if the victim is dead, add 5 extra gold
        if (victim.getHPVal() == 0) this->modGold(5);
    } else {
        victim.modHP(0);
    }
}

void Goblin::beAttacked(Enemy &attacker) {
    // when beAttacked is called, the attack is successful
    // use double to track values for ceil
    double constant = 100;
    double validDef = 100 + this->getDefVal();
    double validAtk = attacker.getAtkVal();
    double multiplier = 1;

    // if attacker is orcs, then does 50% more dmg
    if (attacker.getType() == Type::Orc) multiplier = 1.5;
    
    // use the provided formula
    this->modHP(-(ceil(multiplier * ((constant/validDef) * validAtk))));
}

//provides maxHP
int Goblin::getMaxHP() {
    return maxHP;
}

// calls PC's ctor
Goblin::Goblin(int x, int y) : PC(110, 15, 20, x, y) {}
