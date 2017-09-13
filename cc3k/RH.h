#ifndef RH_h
#define RH_h
#include <memory>
#include "Potion.h"
#include "Type.h"
class PC;

class RH final : public Potion {
public:
    bool useMe(std::shared_ptr<PC> myPC) override; // overrides useMe() to make the effect permanent
    Type getType() const override; // provides the most detailed type
    
    RH(int x, int y); // calls Potion's ctor
};

#endif 
