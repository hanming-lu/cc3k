#include "Normal.h"
int Normal::getValue() {
    // gets the value of the hoard
    return amount * value;
};

// return the most specific type
Type Normal::getType() const {
    return Type::Normal;
};

// 1 or more normal gold spawn at position x, y
Normal::Normal(int x, int y, int amount) : Treasure(x, y), amount{amount} {}
