// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Type_h
#define Type_h
#include <string>
// most detailed type of each Base
enum class Type {
    BA, BD, WA, WD, RH, PH,
    Small, Normal, MerchantHoard, DragonHoard,
    Shade, Drow, Vampire, Troll, Goblin, SuperMan,
    Human, Dwarf, Elf, Orc, Halfling, Dragon, Merchant,
    rand
};
std::string operator*(Type t);
Type operator*(std::string t);

#endif
