// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Dragon_h
#define Dragon_h
#include <string>
#include <memory>
#include "Enemy.h"
#include "Type.h"

class Treasure;

class Dragon final : public Enemy {
    std::weak_ptr<Treasure> myHoard;
public:
    void setHoard(std::shared_ptr<Treasure>) override; // sets myHoard
    std::shared_ptr<Treasure> getHoard() override; // return theHoard
    Type getType() const override; // returns the most detailed Type
    int dropGold() override; // drops 0 gold, only changes myHoard's status
    
    Dragon(std::shared_ptr<Treasure> myHoard, int x, int y); // calls Enemy's ctor
};

#endif
