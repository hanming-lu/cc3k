// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Base_h
#define Base_h
#include "Type.h"
#include "Info.h"
#include "LowerGenre.h"

class Base {
protected:
    Info theInfo;
    Info preInfo;
public:
    Info getPos(); // return the x, y coordinate of the Base using an Info
    Info getPrePos(); // return the previous x, y coordinate of the Base using an Info
    int getx(); // return the x coordinate of the Base
    int gety(); // return the y coordinate of the Base
    int getPrex(); // return the prex coordinate of the Base
    int getPrey(); // return the prey coordinate of the Base
    void setPos(int x, int y); // sets the coordinates of the base
    void setPos(Info pos); // sets the coordinates of the base
    virtual LowerGenre getLowerGenre() const = 0; // return lower genre
    virtual Type getType() const = 0; // return the most detailed Type

    Base(int x, int y);
    virtual ~Base() = default;
    
};

#endif
