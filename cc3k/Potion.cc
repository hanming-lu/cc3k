#include <memory>
#include "Potion.h"
#include "PC.h"
#include "BA.h"
#include "WA.h"
#include "BD.h"
#include "WD.h"
#include "RH.h"
#include "PH.h"

LowerGenre Potion::getLowerGenre() const {
    // return lower genre
    return LowerGenre::Potion;
}

std::shared_ptr<Potion> createPotion(Info theInfo) {
    return createPotion(theInfo.x, theInfo.y);
}

std::shared_ptr<Potion> createPotion(int x, int y) {
    // generate a random Potion at x, y
    std::shared_ptr<Potion> p;
    int race = rand() % 6 + 1;
    if (race == 1) {
        std::shared_ptr<Potion> tmp{new BA(x, y)};
        p = tmp;
    } else if (race == 2) {
        std::shared_ptr<Potion> tmp{new WA(x, y)};
        p = tmp;
    } else if (race == 3) {
        std::shared_ptr<Potion> tmp{new BD(x, y)};
        p = tmp;
    } else if (race == 4) {
        std::shared_ptr<Potion> tmp{new WD(x, y)};
        p = tmp;
    } else if (race == 5) {
        std::shared_ptr<Potion> tmp{new RH(x, y)};
        p = tmp;
    } else {
        std::shared_ptr<Potion> tmp{new PH(x, y)};
        p = tmp;
    }
    return p;
}

// calls Item's ctor
Potion::Potion(int x, int y) : Item(x, y) {}

// dtor
Potion::~Potion() {}
