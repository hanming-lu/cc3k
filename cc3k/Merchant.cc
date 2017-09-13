// Notes left for Suri on dropGold, needs Suri's MerchantHoard.h to compile
#include <cmath>
#include "Merchant.h"
#include "PC.h"
#include "MerchantHoard.h"

bool Merchant::isHostile = false;

void Merchant::setHostile(bool b) {
    // sets the isHostile field
    Merchant::isHostile = b;
}

bool Merchant::getHostile() {
    // gets the isHostile field
    return Merchant::isHostile;
}


void Merchant::beAttacked(PC &attacker) {
    // Merchant becomes hostile after been attacked
    Merchant::isHostile = true;
    
    // when beAttacked is called, the attack is successful
    // use double to track values for ceil
    double constant = 100;
    double validDef = 100 + this->getDefVal();
    double validAtk = attacker.getAtkVal();
    // use the provided formula
    this->modHP(-(ceil((constant/validDef) * validAtk)));
    if (this->getHPVal() == 0) attacker.modGold(this->dropGold());
    
}

// HumanHoard ctor needs to check if x,y has a Merchant, if yes, delete that Merchant
int Merchant::dropGold() {
    return 0;
}

Type Merchant::getType() const {
    // returns the most detailed Type
    return Type::Merchant;
}

// ctor calls Enemy's ctor
Merchant::Merchant(int x, int y) : Enemy(30, 70, 5, x, y) {}
