#ifndef MerchantHoard_h
#define MerchantHoard_h
#include "Treasure.h"
#include "Type.h"

class MerchantHoard final : public Treasure {
    const int value = 4;
public:
    int getValue() override; // gets the value of the hoard
    Type getType() const override; // return the most specific type
    
    MerchantHoard(int x, int y); // a MerchantHoard gold spawns at position x, y
};

#endif
