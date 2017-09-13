// Complete
#include "Character.h"
#include <string>
using namespace std;

int Character::modHP(int modVal) {
    // update previous HP
    this->preHP = this->HP;
    // modify current HP by modVal, return the modified HP
    this->HP += modVal;
    // if 0, the Character is slain
    if (this->HP <= 0) this->HP = 0;
    return this->HP;
}

// return HP value
int Character::getHPVal() {
    return this->HP;
}

// return preHP value
int Character::getPreHPVal() {
    return this->preHP;
}


// return Atk value
int Character::getAtkVal() {
    return this->Atk;
}

// return Def value
int Character::getDefVal() {
    return this->Def;
}

bool Character::isDead() {
    // return true if PC is dead
    if (getHPVal() == 0) return true;
    return false;
}

//ctor calls Base's ctor
Character::Character(int HP, int Atk, int Def, int x, int y) : Base(x, y), HP{HP}, preHP{HP}, Atk{Atk}, Def{Def} {}

// dtor
Character::~Character() {}
