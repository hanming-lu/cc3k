#ifndef Normal_h
#define Normal_h
#include "Treasure.h"
#include "Type.h"

class Normal final : public Treasure {
    const int value = 2;
    const int amount;
public:
    int getValue() override; // gets the value of the hoard
    Type getType() const override; // return the most specific type
    
    Normal(int x, int y, int amount = 1); // 1 or more normal gold spawn at position x, y
};
#endif
