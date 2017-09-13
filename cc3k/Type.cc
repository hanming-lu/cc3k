#include "Type.h"
#include <string>

std::string operator*(Type t) {
    if (t == Type::Shade) return "Shade";
    if (t == Type::Drow) return "Drow";
    if (t == Type::Vampire) return "Vampire";
    if (t == Type::Troll) return "Troll";
    if (t == Type::Goblin) return "Goblin";
    if (t == Type::SuperMan) return "SuperMan";
    
    if (t == Type::Human) return "Human";
    if (t == Type::Dwarf) return "Dwarf";
    if (t == Type::Elf) return "Elf";
    if (t == Type::Orc) return "Orc";
    if (t == Type::Halfling) return "Halfling";
    if (t == Type::Dragon) return "Dragon";
    if (t == Type::Merchant) return "Merchant";
    
    if (t == Type::BA) return "BA";
    if (t == Type::BD) return "BD";
    if (t == Type::WA) return "WA";
    if (t == Type::WD) return "WD";
    if (t == Type::RH) return "RH";
    if (t == Type::PH) return "PH";
    
    if (t == Type::Small) return "Small";
    if (t == Type::Normal) return "Normal";
    if (t == Type::MerchantHoard) return "MerchantHoard";
    if (t == Type::DragonHoard) return "DragonHoard";
    
    if (t == Type::rand) return "rand";
    
    return "";
}

Type operator*(std::string t) {
    if (t == "Shade") return Type::Shade;
    if (t == "Drow") return Type::Drow;
    if (t == "Vampire") return Type::Vampire;
    if (t == "Troll") return Type::Troll;
    if (t == "Goblin") return Type::Goblin;
    if (t == "SuperMan") return Type::SuperMan;
    if (t == "s") return Type::Shade;
    if (t == "d") return Type::Drow;
    if (t == "v") return Type::Vampire;
    if (t == "t") return Type::Troll;
    if (t == "g") return Type::Goblin;
    if (t == "sp") return Type::SuperMan;
    
    if (t == "Human") return Type::Human;
    if (t == "Dwarf") return Type::Dwarf;
    if (t == "Elf") return Type::Elf;
    if (t == "Orc") return Type::Orc;
    if (t == "Halfling") return Type::Halfling;
    if (t == "Dragon") return Type::Dragon;
    if (t == "Merchant") return Type::Merchant;
    
    if (t == "BA") return Type::BA;
    if (t == "BD") return Type::BD;
    if (t == "WA") return Type::WA;
    if (t == "WD") return Type::WD;
    if (t == "RH") return Type::RH;
    if (t == "PH") return Type::PH;
    
    if (t == "Small") return Type::Small;
    if (t == "Normal") return Type::Normal;
    if (t == "MerchantHoard") return Type::MerchantHoard;
    if (t == "DragonHoard") return Type::DragonHoard;
    
    return Type::rand;
}
