#ifndef Small_h
#define Small_h
#include "Treasure.h"
#include "Type.h"

class Small final : public Treasure {
    const int value = 1;
public:
    int getValue() override; // gets the value of the hoard
    Type getType() const override; // return the most specific type
    
    Small(int x, int y); // a small gold spawn at position x, y
};


#endif
