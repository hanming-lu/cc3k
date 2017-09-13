// Complete
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "PC.h"
#include "Enemy.h"

int PC::modHP(int modVal) {
    this->preHP = this->HP;
    // modify current HP by modVal, return the modified HP
    this->HP += modVal;
    // if 0, the Character is slain
    if (this->HP < 0) this->HP = 0;
    // Cannot be above maxHP
    if (this->HP > this->getMaxHP()) this->HP = this->getMaxHP();
    // return current HP
    return this->HP;
}

// modifies gold by modVal amount
void PC::modGold(int modVal) {
    // DLC: if can buy, need to check if gold is negative
    this->prepregold = this->pregold;
    this->pregold = this->gold;
    this->gold += modVal;
}

int PC::getGold() {
    // get the gold
    return gold;
}
int PC::getPreGold() {
    // get the Pregold
    return pregold;
}

int PC::getPrePreGold() {
    return prepregold;
}

void PC::rmEffect() {
    // clear tmpPotions
    tmpPotions.clear();
}

void PC::attack(Enemy &victim) {
    // track if the victim is halfling, if yes, then 50% chance to miss
    int validAttack = 1;
    if (victim.getType() == Type::Halfling) {
        validAttack = rand() % 2;
    }
    // if attack is valid, then call beAttacked on the victim
    if (validAttack) {
        victim.beAttacked(*this);
    } else {
        victim.modHP(0);
    }
}

void PC::beAttacked(Enemy &attacker) {
    // when beAttacked is called, the attack is successful
    // use double to track values for ceil
    double constant = 100;
    double validDef = 100 + this->getDefVal();
    double validAtk = attacker.getAtkVal();
    // use the provided formula
    this->modHP(-(ceil((constant/validDef) * validAtk)));
}

int PC::getAtkVal() {
    // return the after potion Atk value
    int tmp = this->Atk + tmpPotions[Type::BA] * 5 - tmpPotions[Type::WA] * 5;
    if (tmp < 0) return 0;
    return tmp;
}

int PC::getDefVal() {
    // return the after potion Def value
    int tmp = this->Def + tmpPotions[Type::BD] * 5 - tmpPotions[Type::WD] * 5;
    if (tmp < 0) return 0;
    return tmp;
}

void PC::usePotion(Type thePotion){
    // add thePotion to the tmpPotions array
    tmpPotions[thePotion] = tmpPotions[thePotion] + 1;
}


// return lower genre
LowerGenre PC::getLowerGenre() const {
    return LowerGenre::PC;
}


// ctor calls Character's ctor
PC::PC(int HP, int Atk, int Def, int x, int y) : Character(HP, Atk, Def, x, y) {}

// dtor
PC::~PC() {}
