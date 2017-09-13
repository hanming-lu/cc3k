#include <memory>
#include "Treasure.h"
#include "PC.h"
#include "Small.h"
#include "Normal.h"
#include "DragonHoard.h"

std::shared_ptr<Treasure> createTreasure(Info theInfo) {
    return createTreasure(theInfo.x, theInfo.y);
}

std::shared_ptr<Treasure> createTreasure(int x, int y) {
    // generate a random Treasure at x, y
    std::shared_ptr<Treasure> p;
    int race = rand() % 8 + 1;
    if (race >= 1 && race <= 2) {
        std::shared_ptr<Treasure> tmp{new Small(x, y)}; // chance of 1/4
        p = tmp;
    } else if (race >= 3 && race <= 7) {
        std::shared_ptr<Treasure> tmp{new Normal(x, y)}; // chance of 5/8
        p = tmp;
    } else {
        std::shared_ptr<Treasure> tmp{new DragonHoard(x, y)}; // chance of 1/8
        p = tmp;
    }
    return p;
}

bool Treasure::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Most treasures
    myPC->modGold(this->getValue());
    return true;
}

void Treasure::setDragon(std::shared_ptr<Enemy> theDragon) {
    // sets the dragon guardian
    this->theDragon = theDragon;
}

std::shared_ptr<Enemy> Treasure::getDragon() {
    // gets the dragon pointer
    return theDragon.lock();
}

bool Treasure::guarded() {
    // return if treasure is guarded
    return isGuarded;
}


void Treasure::dragonSlain() {
    // this method is called when dragon is slain, changes isGuarded to false
    isGuarded = false;
}


LowerGenre Treasure::getLowerGenre() const {
    // return lower genre
    return LowerGenre::Treasure;
}

// calls Item's ctor, spawn at position x, y
Treasure::Treasure(int x, int y) : Item(x, y) {}

// dtor
Treasure::~Treasure() {}
