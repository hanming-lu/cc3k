// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Orc_h
#define Orc_h
#include "Enemy.h"
#include "Type.h"

class Orc final : public Enemy {
public:
    Type getType() const override; // returns the most detailed Type
    
    Orc(int x, int y); // calls Enemy's ctor
};

#endif
