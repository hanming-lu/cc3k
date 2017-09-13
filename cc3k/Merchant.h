// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Merchant_h
#define Merchant_h
#include "Enemy.h"
#include "Type.h"

class Merchant final : public Enemy {
    static bool isHostile; // will be initialized to false

public:
    static void setHostile(bool); // sets the isHostile field
    static bool getHostile(); // gets the isHostile field
    void beAttacked(PC &attacker) override; // DO NOT call this method dirrectly. attack(Enemy &) will call this method, return true and call attacker.dropGold() if slain.
    Type getType() const override; // returns the most detailed Type
    int dropGold() override; // does not give gold directly, calls MerchantHoard ctor

    Merchant(int x, int y); // calls Enemy's ctor
};

#endif
