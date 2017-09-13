#include <iostream>
#include <string>
#include <vector>
#include "TextDisplay.h"
#include "Base.h"
#include "Floor.h"
#include "PC.h"
#include "Enemy.h"
#include "Potion.h"
#include "Direction.h"
#include "Treasure.h"
using namespace std;

void TextDisplay::updateFloor(std::shared_ptr<Floor> aFloor) {
    myFloor = aFloor;
}

void TextDisplay::notifyPCSpawn(std::shared_ptr<PC> aPC) {
    // set the PC's ptr
    myPC = aPC;
    td[myPC.lock()->gety()][myPC.lock()->getx()] = '@';
    if (myFloor.lock()->getLevel() == 1) {
        addMsg("Your PC has spawn.");
        if (aPC->getType() == Type::Troll) {
            addMsg("You have selected the race Troll, the PC will gain 5 HP every valid turn and HP is capped at 120 HP. Enjoy!");
        } else if (aPC->getType() == Type::Shade) {
            addMsg("You have selected the race Shade, you will gain 50% higher score at the end. Enjoy!");
        } else if (aPC->getType() == Type::Drow) {
            addMsg("You have selected the race Drow, all potions have their effect magnified by 50%. Enjoy!");
        } else if (aPC->getType() == Type::Vampire) {
            addMsg("You have selected the race Vampire, you will gain 5 HP every successful attack and has no maximum HP. But watchout for Dwarves! Enjoy!");
        } else if (aPC->getType() == Type::Goblin) {
            addMsg("You have selected the race Goblin, you will gain 5 extra gold every time you slay an Enemy! Enjoy!");
        }  else if (aPC->getType() == Type::SuperMan) {
            addMsg("You have selected the race SuperMan, only the sky is your limit! Enjoy!");
        }
    }
}

void TextDisplay::notifySpawn(std::shared_ptr<Base> aBase) {
    // update the spawn td
    if(aBase->getLowerGenre() == LowerGenre::Potion) {
        td[aBase->gety()][aBase->getx()] = 'P';
    } else if (aBase->getLowerGenre() == LowerGenre::Treasure) {
        td[aBase->gety()][aBase->getx()] = 'G';
    } else if (aBase->getType() == Type::Human) {
        td[aBase->gety()][aBase->getx()] = 'H';
    } else if (aBase->getType() == Type::Dwarf) {
        td[aBase->gety()][aBase->getx()] = 'W';
    } else if (aBase->getType() == Type::Elf) {
        td[aBase->gety()][aBase->getx()] = 'E';
    } else if (aBase->getType() == Type::Orc) {
        td[aBase->gety()][aBase->getx()] = 'O';
    } else if (aBase->getType() == Type::Merchant) {
        td[aBase->gety()][aBase->getx()] = 'M';
    } else if (aBase->getType() == Type::Dragon) {
        td[aBase->gety()][aBase->getx()] = 'D';
    } else if (aBase->getType() == Type::Halfling) {
        td[aBase->gety()][aBase->getx()] = 'L';
    }
}

void TextDisplay::notifySpawn(char c, Info i) {
    // spawn the stair
    td[i.y][i.x] = c;
}

void TextDisplay::notifyPCMove() {
    // update the before and after locations, (check if any treasure in pre x, y)
    Info nowPos = myPC.lock()->getPos();
    Info prePos = myPC.lock()->getPrePos();
    td[nowPos.y][nowPos.x] = '@';
    if (myFloor.lock()->getTreasure(prePos) == nullptr) {
        td[prePos.y][prePos.x] = stdtd[prePos.y][prePos.x];
    } else {
        td[prePos.y][prePos.x] = 'G';
    }
}

void TextDisplay::notifyMove(std::shared_ptr<Enemy> aEnemy) {
    // update the before and after locations, print msg
    if (aEnemy->getType() == Type::Human) {
        td[aEnemy->gety()][aEnemy->getx()] = 'H';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    } else if (aEnemy->getType() == Type::Dwarf) {
        td[aEnemy->gety()][aEnemy->getx()] = 'W';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    } else if (aEnemy->getType() == Type::Elf) {
        td[aEnemy->gety()][aEnemy->getx()] = 'E';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    } else if (aEnemy->getType() == Type::Orc) {
        td[aEnemy->gety()][aEnemy->getx()] = 'O';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    } else if (aEnemy->getType() == Type::Merchant) {
        td[aEnemy->gety()][aEnemy->getx()] = 'M';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    } else if (aEnemy->getType() == Type::Dragon) {
    } else if (aEnemy->getType() == Type::Halfling) {
        td[aEnemy->gety()][aEnemy->getx()] = 'L';
        td[aEnemy->getPrey()][aEnemy->getPrex()] = '.';
    }
}

void TextDisplay::notifyDead(std::shared_ptr<Base> aBase) {
    // if not Treasure, update the location char, print msg based on type
    if (!(aBase->getLowerGenre() == LowerGenre::Treasure)) {
        td[aBase->gety()][aBase->getx()] = '.';
    }
}

char TextDisplay::getChar(Info aInfo) {
    // return the Char on td at Info
    return td[aInfo.y][aInfo.x];
}

// modify msg
void TextDisplay::addMsg(std::string aNewMsg) {
    // add msg to msg
    this->msg += aNewMsg;
    this->msg += " ";
}
void TextDisplay::addPCMoveMsg(Direction theDir) {
    // add PC move message
    if (theDir == Direction::no) addMsg("PC moves one step to the North.");
    if (theDir == Direction::so) addMsg("PC moves one step to the South.");
    if (theDir == Direction::ea) addMsg("PC moves one step to the East.");
    if (theDir == Direction::we) addMsg("PC moves one step to the West.");
    if (theDir == Direction::ne) addMsg("PC moves one step to the Northeast.");
    if (theDir == Direction::nw) addMsg("PC moves one step to the Northwest.");
    if (theDir == Direction::se) addMsg("PC moves one step to the Southeast.");
    if (theDir == Direction::sw) addMsg("PC moves one step to the Southwest.");
    if (theDir == Direction::tp) addMsg("PC teleports to (" + to_string(myPC.lock()->getx()) + ", " + to_string(myPC.lock()->gety()) + ").");
}

void TextDisplay::addAttackMsg(std::shared_ptr<Enemy> aEnemy) {
    // add an Attack Msgif (myPC->getPreHPVal() - myPC->getHPVal() == 0) {
    if (aEnemy->getPreHPVal() - aEnemy->getHPVal() == 0) {
        addMsg("PC missed their attack.");
    } else {
        addMsg("PC attacked a " + *(aEnemy->getType()) + ", dealing " + to_string(aEnemy->getPreHPVal() - aEnemy->getHPVal()) + " damage.");
    }
    if (aEnemy->getHPVal() != 0) {
        addMsg("The opponent's current HP is: " + to_string(aEnemy->getHPVal()) + ".");
    }
}

void TextDisplay::addBeAttackMsg(std::shared_ptr<Enemy> aEnemy) {
    // add a beattacked Msg
    if (myPC.lock()->getPreHPVal() - myPC.lock()->getHPVal() == 0) {
        addMsg(*(aEnemy->getType()) + " missed their attack.");
    } else {
        addMsg("PC was attacked by a " + *(aEnemy->getType()) + ", dealing " + to_string(myPC.lock()->getPreHPVal() - myPC.lock()->getHPVal()) + " damage.");
    }
    addMsg("PC's current HP is: " + to_string(myPC.lock()->getHPVal()) + ".");
}

void TextDisplay::addSlayMsg(std::shared_ptr<Enemy> aEnemy) {
    // add a slaying and gold gain Msg
    addMsg("PC has slain a");
    if (myPC.lock()->getType() == Type::Goblin) {
        if (aEnemy->getType() == Type::Human) {
            addMsg("Human, gaining 5 extra gold.");
        } else if (aEnemy->getType() == Type::Dwarf) {
            addMsg("Dwarf, gaining " + to_string(myPC.lock()->getPreGold() - myPC.lock()->getPrePreGold()) + " + 5 extra gold.");
        } else if (aEnemy->getType() == Type::Elf) {
            addMsg("Elf, gaining " + to_string(myPC.lock()->getPreGold() - myPC.lock()->getPrePreGold()) + " + 5 extra gold.");
        } else if (aEnemy->getType() == Type::Orc) {
            addMsg("Orc, gaining " + to_string(myPC.lock()->getPreGold() - myPC.lock()->getPrePreGold()) + " + 5 extra gold.");
        } else if (aEnemy->getType() == Type::Merchant) {
            addMsg("Merchant, gaining 5 extra gold.");
        } else if (aEnemy->getType() == Type::Dragon) {
            addMsg("Dragon, gaining 5 extra gold. The DragonHoard is no longer guarded. ");
        } else if (aEnemy->getType() == Type::Halfling) {
            addMsg("Halfling, gaining " + to_string(myPC.lock()->getPreGold() - myPC.lock()->getPrePreGold()) + " + 5 extra gold.");
        }
    } else {
        if (aEnemy->getType() == Type::Human) {
            addMsg("Human.");
        } else if (aEnemy->getType() == Type::Dwarf) {
            addMsg("Dwarf, gaining " + to_string(myPC.lock()->getGold() - myPC.lock()->getPreGold()) + " gold.");
        } else if (aEnemy->getType() == Type::Elf) {
            addMsg("Elf, gaining " + to_string(myPC.lock()->getGold() - myPC.lock()->getPreGold()) + " gold.");
        } else if (aEnemy->getType() == Type::Orc) {
            addMsg("Orc, gaining " + to_string(myPC.lock()->getGold() - myPC.lock()->getPreGold()) + " gold.");
        } else if (aEnemy->getType() == Type::Merchant) {
            addMsg("Merchant.");
        } else if (aEnemy->getType() == Type::Dragon) {
            addMsg("Dragon, the DragonHoard is no longer guarded.");
        } else if (aEnemy->getType() == Type::Halfling) {
            addMsg("Halfling, gaining " + to_string(myPC.lock()->getGold() - myPC.lock()->getPreGold()) + " gold.");
        }
    }
}

void TextDisplay::addSpawnMsg(std::shared_ptr<Base> aBase) {
    // add a spawn msg
    if (aBase->getType() == Type::MerchantHoard) {
        addMsg("A MerchantHoard is spawned.");
    } else if (aBase->getType() == Type::Normal) {
        addMsg("2 piles of Normal gold is spawned.");
    }
}
void TextDisplay::addUseMsg(std::shared_ptr<Potion> aPotion) {
    // add a Potion use and effect Msg
    if (aPotion->getType() == Type::BA) {
        addMsg("A Bonus Atk potion is used, Atk is temporarily increased, current Atk is: " + to_string(myPC.lock()->getAtkVal()));
    } else if (aPotion->getType() == Type::BD) {
        addMsg("A Bonus Def potion is used, Def is temporarily increased, current Def is: " + to_string(myPC.lock()->getDefVal()));
    } else if (aPotion->getType() == Type::WA) {
        addMsg("A Wound Atk potion is used, Atk is temporarily decreased, current Atk is: " + to_string(myPC.lock()->getAtkVal()));
    } else if (aPotion->getType() == Type::WD) {
        addMsg("A Wound Def potion is used, Def is temporarily decreased, current Def is: " + to_string(myPC.lock()->getDefVal()));
    } else if (aPotion->getType() == Type::RH) {
        addMsg("A Restore Health potion is used, HP is permanently increased, current HP is: " + to_string(myPC.lock()->getHPVal()));
    } else if (aPotion->getType() == Type::PH) {
        addMsg("A Poison Health potion is used, HP is permanently decreased, current HP is: " + to_string(myPC.lock()->getHPVal()));
    }
}

void TextDisplay::addUseMsg(std::shared_ptr<Treasure> aTreasure) {
    // add a Treasure use and gold gain Msg
    //Small, Normal, MerchantHoard, HumanHoard, DragonHoard,
    if (aTreasure->getType() == Type::Small) {
        addMsg("PC picked up a small treasure, gaining 1 gold.");
    } else if (aTreasure->getType() == Type::Normal) {
        if (myPC.lock()->getGold() - myPC.lock()->getPreGold() == 2) {
            addMsg("PC picked up a normal treasure, gaining 2 gold.");
        } else {
            addMsg("PC picked up 2 normal treasures, gaining 4 gold.");
        }
    } else if (aTreasure->getType() == Type::MerchantHoard) {
        addMsg("PC picked up a MerchantHoard, gaining 4 gold.");
    } else if (aTreasure->getType() == Type::DragonHoard) {
        addMsg("PC picked up a DragonHoard, gaining 6 gold.");
    }
}

void TextDisplay::addInvalCmdMsg() {
    addMsg("Invalid Command.");
}

void TextDisplay::addNotUseMsg(std::shared_ptr<Treasure>) {
    // add a Treasure not used no gold gain Msg
    addMsg("Nice try, but Dragons always keep an eye on their DragonHoard.");
}

void TextDisplay::clearMsg() {
    // clears msg in the beginning of each turn
    msg.clear();
}


TextDisplay::TextDisplay() {
    for (int row = 0; row <= 24; ++row) {
        stdtd.emplace_back();
        td.emplace_back();
        for (int col = 0; col <= 78; ++col) {
            stdtd[row].emplace_back();
            td[row].emplace_back();
        }
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    // print out the tb map, with status and msg
    
    for (int row = 24; row >= 0; --row) {
        for (int col = 0; col <= 78; ++col) {
            out << td.td[row][col];
        }
        out << endl;
    }
     

    out << "Race: " + *(td.myPC.lock()->getType()) + " Gold: " << td.myPC.lock()->getGold() << " Floor Level: " << td.myFloor.lock()->getLevel() << endl;
    out << "HP: " << td.myPC.lock()->getHPVal() << endl;
    out << "Atk: " << td.myPC.lock()->getAtkVal() << endl;
    out << "Def: " << td.myPC.lock()->getDefVal() << endl;
    out << "Action: " + td.msg << endl;
    return out;
}

void TextDisplay::setWindow(WINDOW * aWin) {
    curwin = aWin;
}

WINDOW *TextDisplay::getWindow() {
    // get the window to print
    return curwin;
}


void TextDisplay::windowPrint() {
    for (int row = 0; row <= 40; ++row) {
        for (int col = 0; col <= 80; ++col) {
            mvwaddch(curwin, row, col, ' ');

        }
    }
    
    // x: 0-78, y: 1-25
    for (int row = 24; row >= 0; --row) {
        for (int col = 0; col <= 78; ++col) {
            mvwaddch(curwin, 25-row, col, td[row][col]);
        }
    }
    
    // y: 26-30
    string line26 = "Race: " + *(myPC.lock()->getType()) + " Gold: " + to_string(myPC.lock()->getGold()) + " Floor Level: " + to_string(myFloor.lock()->getLevel());
    string line27 = "HP: " + to_string(myFloor.lock()->getMyPC()->getHPVal());
    string line28 = "Atk: " + to_string(myPC.lock()->getAtkVal());
    
    string line29 = "Def: " + to_string(myPC.lock()->getDefVal());
    string line30 = "Action: " + msg;
    
    mvwprintw(curwin, 26, 0, line26.c_str());
    mvwprintw(curwin, 27, 0, line27.c_str());
    mvwprintw(curwin, 28, 0, line28.c_str());
    mvwprintw(curwin, 29, 0, line29.c_str());
    mvwprintw(curwin, 30, 0, line30.c_str());
    
    wrefresh(curwin);
}
