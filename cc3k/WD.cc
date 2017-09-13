#include "WD.h"
#include "PC.h"
#include "Type.h"

bool WD::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    myPC->usePotion(this->getType());
    return true;
};

Type WD::getType() const {
    // provides the most detailed type
    return Type::WD;
}

// calls Potion's ctor
WD::WD(int x, int y) : Potion(x, y) {}
