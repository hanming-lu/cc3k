// Complete
#include "Base.h"
Info Base::getPos() {
    // return the x, y coordinate of the Base using an Info
    return theInfo;
}

Info Base::getPrePos() {
    // return the previous x, y coordinate of the Base using an Info
    return preInfo;
}

int Base::getx() {
    // return the x coordinate of the Base
    return theInfo.x;
}

int Base::gety() {
    // return the y coordinate of the Base
    return theInfo.y;
}

int Base::getPrex() {
    // return the prex coordinate of the Base
    return preInfo.x;
}

int Base::getPrey() {
    // return the prey coordinate of the Base
    return preInfo.y;
}


void Base::setPos(int x, int y) {
    // update previous x, y
    preInfo.x = theInfo.x;
    preInfo.y = theInfo.y;
    
    // sets the coordinates of the base
    theInfo.x = x;
    theInfo.y = y;
}

void Base::setPos(Info pos) {
    // calls setPos(int, int)
    preInfo = theInfo;
    theInfo = pos;
}

// ctor using passed coords
Base::Base(int x, int y) : theInfo(x, y), preInfo(x,y) {}
