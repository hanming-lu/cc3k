#include "WA.h"
#include "PC.h"
#include "Type.h"

bool WA::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    myPC->usePotion(this->getType());
    return true;
};

Type WA::getType() const {
    // provides the most detailed type
    return Type::WA;
}

// calls Potion's ctor
WA::WA(int x, int y) : Potion(x, y) {}
