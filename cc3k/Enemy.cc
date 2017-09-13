// Complete
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <memory>
#include "Enemy.h"
#include "PC.h"
#include "Human.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
using namespace std;

void Enemy::setHoard(std::shared_ptr<Treasure>) {}

std::shared_ptr<Treasure> Enemy::getHoard() {
    return nullptr;
}


int Enemy::dropGold() {
    // randomly generate a small(value 1) or normal(value 2) gold
    int instantGoldVal = rand() % 2 + 1;
    
    return instantGoldVal;
}

void Enemy::attack(PC &victim, int curTurn) {
    
    // 50% chance missing
    int validAttack = rand() % 2;
    
    // if attack is valid, then call beAttacked on the victim
    if (validAttack) {
        victim.beAttacked(*this);
    } else {
        victim.modHP(0);
    }
    
    // sets turn to be curTurn
    this->setTurn(curTurn);
}

void Enemy::beAttacked(PC &attacker) {
    // when beAttacked is called, the attack is successful
    // use double to track values for ceil
    double constant = 100;
    double validDef = 100 + this->getDefVal();
    double validAtk = attacker.getAtkVal();
    // use the provided formula
    this->modHP(-(ceil((constant/validDef) * validAtk)));
    if (this->getHPVal() == 0) attacker.modGold(this->dropGold());
}

std::shared_ptr<Enemy>createEnemy(Info theInfo) {
    return createEnemy(theInfo.x, theInfo.y);
}

shared_ptr<Enemy> createEnemy(int x, int y) {
    // randomly generate an enemy race at the position x, y
    int race = rand() % 18 + 1;
    shared_ptr<Enemy> p;
    if (race >= 1 && race <= 4) {
        shared_ptr<Enemy> tmp{new Human(x, y)};// chance of 2/9
        p = tmp;
    } else if (race >= 5 && race <= 7) {
        shared_ptr<Enemy> tmp{new Dwarf(x, y)};// chance of 2/9
        p = tmp;
    } else if (race >= 8 && race <= 12) {
        shared_ptr<Enemy> tmp{new Halfling(x, y)};// chance of 2/9
        p = tmp;
    } else if (race >= 13 && race <= 14) {
        shared_ptr<Enemy> tmp{new Elf(x, y)};// chance of 2/9
        p = tmp;
    } else if (race >= 15 && race <= 16) {
        shared_ptr<Enemy> tmp{new Orc(x, y)};// chance of 2/9
        p = tmp;
    } else {
        shared_ptr<Enemy> tmp{new Merchant(x, y)};// chance of 2/9
        p = tmp;
    }
    return p;
}

void Enemy::setTurn(int curTurn) {
    // sets the turn to be curTurn
    turn = curTurn;
}

int Enemy::getTurn() {
    // return the turn field
    return turn;
}

// return lower genre
LowerGenre Enemy::getLowerGenre() const {
    return LowerGenre::Enemy;
}

// ctor calls Character's ctor
Enemy::Enemy(int HP, int Atk, int Def, int x, int y) : Character(HP, Atk, Def, x, y) {}

// dtor
Enemy::~Enemy() {}
