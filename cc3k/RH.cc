#include "RH.h"
#include "PC.h"
#include "Type.h"

bool RH::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    if (myPC->getType() == Type::Drow) {
        myPC->modHP(15);
    } else {
        myPC->modHP(10);
    }
    return true;
};

Type RH::getType() const {
    // provides the most detailed type
    return Type::RH;
}

// calls Potion's ctor
RH::RH(int x, int y) : Potion(x, y) {}
