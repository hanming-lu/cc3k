#ifndef DragonHoard_h
#define DragonHoard_h
#include <memory>
#include "Treasure.h"
#include "Type.h"

class DragonHoard final : public Treasure {
    const int value = 6;
    
public:
    bool useMe(std::shared_ptr<PC> myPC) override; // the useMe for DragonHoard
    int getValue() override; // gets the value of the hoard
    Type getType() const override; // return the most specific type
    
    DragonHoard(int x, int y); // a MerchantHoard gold spawns at position x, y, calls Dragon's ctor on a random place
};
#endif
