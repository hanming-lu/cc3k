#include "Info.h"
// define ==
bool operator==(Info i1, Info i2) {
    if ((i1.x == i2.x) && (i1.y == i2.y)) return true;
    return false;
}

// return direction info
Info retDirInfo(Info i, Direction theDir) {
    if (theDir == Direction::no) {
        i.y = i.y + 1;
        return i;
    } else if (theDir == Direction::so) {
        i.y = i.y - 1;
        return i;
    } else if (theDir == Direction::ea) {
        i.x = i.x + 1;
        return i;
    } else if (theDir == Direction::we) {
        i.x = i.x - 1;
        return i;
    } else if (theDir == Direction::ne) {
        i.y = i.y + 1;
        i.x = i.x + 1;
        return i;
    } else if (theDir == Direction::nw) {
        i.y = i.y + 1;
        i.x = i.x - 1;
        return i;
    } else if (theDir == Direction::se) {
        i.y = i.y - 1;
        i.x = i.x + 1;
        return i;
    } else {
        // theDir == Direction::sw
        i.y = i.y - 1;
        i.x = i.x - 1;
        return i;
    }
}

Info::Info(int x, int y) : x{x}, y{y} {}

