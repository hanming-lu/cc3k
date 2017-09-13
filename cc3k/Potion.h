#ifndef Potion_h
#define Potion_h
#include <memory>
#include "Item.h"
#include "LowerGenre.h"
class PC;

class Potion : public Item {
public:
    LowerGenre getLowerGenre() const override; // return lower genre

    Potion(int x, int y); // calls Item's ctor
    virtual ~Potion() = 0;
    
    friend std::shared_ptr<Potion> createPotion(Info theInfo);
    friend std::shared_ptr<Potion> createPotion(int x, int y); // randomly generate a genre item at the position x, y
};

std::shared_ptr<Potion> createPotion(Info theInfo); // randomly generate a genre item at the Info
std::shared_ptr<Potion> createPotion(int x, int y); // randomly generate a genre item at the position x, y

#endif
