#include "PH.h"
#include "PC.h"
#include "Type.h"

bool PH::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    if (myPC->getType() == Type::Drow) {
        myPC->modHP(-15);
    } else {
        myPC->modHP(-10);
    }
    return true;
};

Type PH::getType() const {
    // provides the most detailed type
    return Type::PH;
}

// calls Potion's ctor
PH::PH(int x, int y) : Potion(x, y) {}
