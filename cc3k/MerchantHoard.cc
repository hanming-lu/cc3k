#include "MerchantHoard.h"
int MerchantHoard::getValue() {
    // gets the value of the hoard
    return value;
}

Type MerchantHoard::getType() const {
    // return the most specific type
    return Type::MerchantHoard;
}

// a MerchantHoard gold spawns at position x, y
MerchantHoard::MerchantHoard(int x, int y) : Treasure(x, y) {}
