// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Halfling_h
#define Halfling_h
#include "Enemy.h"
#include "Type.h"

class Halfling final : public Enemy {

public:
    Type getType() const override; // returns the most detailed Type

    Halfling(int x, int y); // calls Enemy's ctor
};

#endif
