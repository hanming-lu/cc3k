#ifndef Treasure_h
#define Treasure_h
#include <memory>
#include "Item.h"
#include "LowerGenre.h"
class Enemy;
class Dragon;
class PC;

class Treasure : public Item {
    virtual int getValue() = 0; // gets the value of the hoard

protected:
    bool isGuarded = true;
    std::weak_ptr<Enemy> theDragon;

public:
    virtual bool useMe(std::shared_ptr<PC> myPC) override; // the useMe for most Treasures
    LowerGenre getLowerGenre() const override; // return lower genre
    void setDragon(std::shared_ptr<Enemy> theDragon); // sets the dragon guardian
    std::shared_ptr<Enemy> getDragon(); // gets the dragon pointer
    void dragonSlain(); // this method is called when dragon is slain, changes isGuarded to false
    bool guarded(); // return if treasure is guarded

    Treasure(int x, int y); // calls Item's ctor, spawn at position x, y
    virtual ~Treasure() = 0;
    friend std::shared_ptr<Treasure> createTreasure(Info theInfo);
    friend std::shared_ptr<Treasure> createTreasure(int x, int y); // randomly generate a genre item at the position x, y

};

std::shared_ptr<Treasure> createTreasure(Info theInfo); // randomly generate a genre item at the Info
std::shared_ptr<Treasure> createTreasure(int x, int y); // randomly generate a genre item at the position x, y
#endif
