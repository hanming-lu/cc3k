#include "BA.h"
#include "PC.h"
#include "Type.h"

bool BA::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    myPC->usePotion(this->getType());
    return true;
};

Type BA::getType() const {
    // provides the most detailed type
    return Type::BA;
}

// calls Potion's ctor
BA::BA(int x, int y) : Potion(x, y) {}
