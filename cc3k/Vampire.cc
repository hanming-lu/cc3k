// Notes left for Sheldon for attack() method, Complete
#include <stdlib.h>
#include <time.h>
#include <climits>
#include "Vampire.h"
#include "Enemy.h"

int Vampire::modHP(int modVal) {
    // no maxHP limit
    // update previous HP
    this->preHP = this->HP;
    // modify current HP by modVal, return the modified HP
    this->HP += modVal;
    // if 0, the Character is slain
    if (this->HP < 0) this->HP = 0;
    // return current HP
    return this->HP;
}

int Vampire::getMaxHP() {
    // unlimited HP, this method won't be called
    return INT_MAX;
}

// when attack is called, need to check if Vampire is still alive
void Vampire::attack(Enemy &victim) {
    // attack is usually valid
    int validAttack = 1;
    int specialHPEffect = 5;
    
    // track if the victim is halfling, if yes, then 50% chance to miss
    if (victim.getType() == Type::Halfling) {
        validAttack = rand() % 2;
    }
    
    // check if victim is Dwarf, if yes, change positive effect to negative effect
    if (victim.getType() == Type::Dwarf) {
        specialHPEffect = -5;
    }
    
    // if attack is valid, then call beAttacked on the victim
    if (validAttack) {
        modHP(specialHPEffect);
        victim.beAttacked(*this);
    } else {
        victim.modHP(0);
    }
}

Type Vampire::getType() const {
    // return the most detailed type
    return Type::Vampire;
}

// calls PC's ctor
Vampire::Vampire(int x, int y) : PC(50, 25, 25, x, y) {}
