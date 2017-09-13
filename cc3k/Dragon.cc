// Need Suri's DragonHoard.h to compile, need to change isGuard to public
#include "Dragon.h"
#include "Treasure.h"

Type Dragon::getType() const {
    // returns the most detailed Type
    return Type::Dragon;
}

int Dragon::dropGold() {
    // drops 0 gold, only changes myHoard's status
    std::shared_ptr<Treasure> tmp = myHoard.lock();
    tmp->dragonSlain();
    return 0;
}

void Dragon::setHoard(std::shared_ptr<Treasure> aTrea) {
    myHoard = aTrea;
}

std::shared_ptr<Treasure> Dragon::getHoard() {
    std::shared_ptr<Treasure> tmp = myHoard.lock();
    return tmp;
}

// ctor calls Enemy's ctor
Dragon::Dragon(std::shared_ptr<Treasure> myHoard, int x, int y) : Enemy(150, 20, 20, x, y), myHoard{myHoard} {}
