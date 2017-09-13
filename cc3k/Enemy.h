// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Enemy_h
#define Enemy_h
#include <memory>
#include "Character.h"
#include "LowerGenre.h"

class Treasure;
class PC;

class Enemy : public Character {
    int turn = 0;

public:
    virtual void setHoard(std::shared_ptr<Treasure>); // sets myHoard
    virtual std::shared_ptr<Treasure> getHoard(); // gets myHoard
    virtual int dropGold(); // drops rand gold when slain
    virtual void attack(PC &victim, int curTurn) ; // 50% chance missing
    virtual void beAttacked(PC &attacker) ; // DO NOT call this method dirrectly. attack(Enemy &) will call this method, return true and call attacker.dropGold() if slain.
    void setTurn(int curTurn); // sets the turn to be curTurn
    int getTurn(); // return the turn field
    LowerGenre getLowerGenre() const override; // return lower genre
    
    Enemy(int HP, int Atk, int Def, int x, int y); // calls Character's ctor
    virtual ~Enemy() = 0;
    
    friend std::shared_ptr<Enemy> createEnemy(Info theInfo); // randomly generate an enemy race at the Info
    friend std::shared_ptr<Enemy> createEnemy(int x, int y); // randomly generate an enemy race at the position x, y
};

std::shared_ptr<Enemy> createEnemy(Info theInfo); // randomly generate an enemy race at the Info
std::shared_ptr<Enemy> createEnemy(int x, int y); // randomly generate an enemy race at the position x, y

#endif
