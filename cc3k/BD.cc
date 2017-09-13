#include "BD.h"
#include "PC.h"
#include "Type.h"

bool BD::useMe(std::shared_ptr<PC> myPC) {
    // the useMe for Temporary Potions
    myPC->usePotion(this->getType());
    return true;
};

Type BD::getType() const {
    // provides the most detailed type
    return Type::BD;
}

// calls Potion's ctor
BD::BD(int x, int y) : Potion(x, y) {}
