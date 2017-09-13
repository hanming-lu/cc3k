#ifndef Item_h
#define Item_h
#include <string>
#include <memory>
#include "LowerGenre.h"
#include "Base.h"
class PC;

class Item : public Base {
public:
    virtual bool useMe(std::shared_ptr<PC>) = 0; // PV for all items
    
    Item(int x, int y); // calls Base's ctor
    virtual ~Item() = default; // virtual dtor

};
#endif
