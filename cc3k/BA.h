#ifndef BA_h
#define BA_h
#include <memory>
#include "Potion.h"
#include "Type.h"
class PC;

class BA final : public Potion {
public:
    bool useMe(std::shared_ptr<PC> myPC) override; // the useMe for Temporary Potions
    Type getType() const override; // provides the most detailed type
    
    BA(int x, int y); // calls Potion's ctor
};
#endif
