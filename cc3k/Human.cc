// Notes left for Suri on dropGold, needs Suri's HumanHoard.h to compile
#include "Human.h"
#include "Normal.h"
#include "Info.h"

// returns the most detailed Type
Type Human::getType() const {
    return Type::Human;
}

// HumanHoard ctor needs to check if x,y has a Human, if yes, delete that human
// does not give gold directly, calls HumanHoard ctor
int Human::dropGold() {
    return 0;
}

// ctor calls Enemy's ctor
Human::Human(int x, int y) : Enemy(140, 20, 20, x, y) {}
