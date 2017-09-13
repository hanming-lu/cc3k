#include "Small.h"
int Small::getValue() {
    // gets the value of the hoard
    return value;
};

Type Small::getType() const {
    // return the most specific type
    return Type::Small;
}

// a small gold spawn at position x, y
Small::Small(int x, int y) : Treasure(x, y) {}
