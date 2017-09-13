#include "DragonHoard.h"
#include "PC.h"

bool DragonHoard::useMe(std::shared_ptr<PC> myPC) {
    // if the treasure is guarded, cannot be used
    if (isGuarded == true) return false;
    
    // if the treasure is not guarded, can be used
    myPC->modGold(this->getValue());
    return true;
}

int DragonHoard::getValue() {
    // gets the value of the hoard
    return value;
}

Type DragonHoard::getType() const {
    // return the most specific type
    return Type::DragonHoard;
}

// a MerchantHoard gold spawns at position x, y, the main calls Dragon's ctor on a random place beside the DragonHoard
DragonHoard::DragonHoard(int x, int y) : Treasure(x, y) {}
