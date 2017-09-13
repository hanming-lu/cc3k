#include <cstdlib>
#include <climits>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <algorithm>
#include <cmath>
#include "Floor.h"
#include "Info.h"
#include "Base.h"
#include "PC.h"
#include "Enemy.h"
#include "Potion.h"
#include "Treasure.h"
#include "Merchant.h"
#include "TextDisplay.h"
#include "GameStatus.h"
#include "Dragon.h"
#include "Direction.h"
#include "MerchantHoard.h"
#include "DragonHoard.h"
#include "Normal.h"
#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"
#include "SuperMan.h"
#include "Elf.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Orc.h"
#include "Human.h"
#include "Merchant.h"
#include "Dragon.h"
#include "BA.h"
#include "WA.h"
#include "BD.h"
#include "WD.h"
#include "RH.h"
#include "PH.h"
#include "Small.h"
#include "Normal.h"
#include "MerchantHoard.h"
#include "DragonHoard.h"
using namespace std;

bool Floor::getDLC() {
    // return myDLC
    return myDLC;
}

void Floor::setDLC(bool theDLC) {
    myDLC = theDLC;
}

void Floor::incTurn() {
    // increase TURN by 1
    TURN++;
}

void Floor::incLevel() {
    LEVEL++;
}

int Floor::getLevel() {
    return LEVEL;
}

int Floor::getScore() {
    // return Score
    return SCORE;
}

std::shared_ptr<PC> Floor::getMyPC() {
    // return myPC
    return myPC;
}


void Floor::toggleFreeze() {
    // toggle Freeze
    FREEZE = !FREEZE;
}

void Floor::cheatHP() {
    myPC->modHP(1000);
}

void Floor::teleport(int x, int y) {
    if (x < 0 || x > 78 || y < 0 || y > 24) {
        TURN--;
        theTd.lock()->addInvalCmdMsg();
        return;
    }
    // completes all actions, checks, msg for moving the PC
    Info dest = Info(x,y);
    // goes to next level
    if (theTd.lock()->getChar(dest) == '\\') {
        if (LEVEL == 5) {
            if (myPC->getType() == Type::Shade) {
                SCORE = 1.5*(myPC->getGold());
            } else {
                SCORE = myPC->getGold();
            }
            throw GameStatus::Win;
        } else {
            PCHP = myPC->getHPVal();
            PCGold = myPC->getGold();
            myPC->rmEffect();
            incLevel();
            clearAllEPT();
            throw GameStatus::NextLevel;
        }
    }
    if (PCCanMove(dest)) {
        // troll gains 5 HP every turn
        if(myPC->getType() == Type::Troll) myPC->modHP(5);
        // track if there was a Treasure before Char move
        bool isTrea = (theTd.lock()->getChar(dest) == 'G');
        // PC moves to that place
        myPC->setPos(dest);
        // notify the td
        theTd.lock()->notifyPCMove();
        theTd.lock()->addPCMoveMsg(Direction::tp);
        // use the Treasure if there is one
        if (isTrea) {
            useTreasure(dest);
        }
        // enemies attack PC if nearby
        attackPC();
    } else {
        TURN--;
        theTd.lock()->addInvalCmdMsg();
        return;
    }
    moveAllEnemy(TURN);
}

void Floor::RestartGame() {
    // throw a Quit Game status
    throw GameStatus::Restart;
}

void Floor::quitGame() {
    // throw a Quit Game status
    if (myPC->getType() == Type::Shade) {
        SCORE = 1.5*(myPC->getGold());
    } else {
        SCORE = myPC->getGold();
    }
    throw GameStatus::Quit;
}

void Floor::spawnPC(Type t, Info i) {
    // spawns the PC at a random place, update "myPC" field, call theTd's notifyPCSpawn()
    if (i.x == -1) {
        i = randEmptyInfo();
    }
    int tmp = 0;
    if (t == Type::rand) {
        if (myDLC == true) {
            tmp = rand() % 6 + 1;
        } else {
            tmp = rand() % 5 + 1;
        }
        
    }
    if (t == Type::Shade || tmp == 1) {
        shared_ptr<PC> p{new Shade(i.x, i.y)};
        myPC = p;
    } else if (t == Type::Drow || tmp == 2) {
        shared_ptr<PC> p{new Drow(i.x, i.y)};
        myPC = p;
    } else if (t == Type::Vampire || tmp == 3) {
        shared_ptr<PC> p{new Vampire(i.x, i.y)};
        myPC = p;
    } else if (t == Type::Troll || tmp == 4) {
        shared_ptr<PC> p{new Troll(i.x, i.y)};
        myPC = p;
    } else if (t == Type::Goblin || tmp == 5) {
        shared_ptr<PC> p{new Goblin(i.x, i.y)};
        myPC = p;
    } else if (t == Type::SuperMan || tmp == 6) {
        shared_ptr<PC> p{new SuperMan(i.x, i.y)};
        myPC = p;
    }
    theTd.lock()->notifyPCSpawn(myPC);
}

void Floor::spawnStair(Info i) {
    // randomly spawn 1 Stair
    if (i.x != -1) {
        theTd.lock()->notifySpawn('\\', i);
        return;
    }
    Info PCInfo = myPC->getPos();
    for (int i = 0; i < myChamberCoords.size();++i) { // check which Chamber the PC locates in
        if(isInChamb(PCInfo, i)) { // PC is in myChamberCoords[i]
            int targetChamber;
            while (true) {
                // generate a chamber num not as i
                targetChamber = rand() % myChamberCoords.size();
                if (targetChamber != i) break;
            }
            int InfoNum = rand() % myChamberCoords[targetChamber].size(); // an Info in targetChamber
            if (!(isOccupied(myChamberCoords[targetChamber][InfoNum]))) {
                theTd.lock()->notifySpawn('\\', myChamberCoords[targetChamber][InfoNum]);
                return;
            }
        }
    }
}

void Floor::spawnEnemy(Type t, Info i) {
    // randomly spawn 1 enemy
    if (i.x == -1) {
        i = randEmptyInfo();
    }
    shared_ptr<Enemy> p;
    if (t == Type::rand) {
        shared_ptr<Enemy> tmp = createEnemy(i);
        p = tmp;
    } else if (t == Type::Human) {
        shared_ptr<Enemy> tmp{new Human(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Dwarf) {
        shared_ptr<Enemy> tmp{new Dwarf(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Elf) {
        shared_ptr<Enemy> tmp{new Elf(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Orc) {
        shared_ptr<Enemy> tmp{new Orc(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Halfling) {
        shared_ptr<Enemy> tmp{new Halfling(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Merchant) {
        shared_ptr<Enemy> tmp{new Merchant(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Dragon) {
        shared_ptr<Enemy> tmp{new Dragon(nullptr,i.x,i.y)};
        p = tmp;
    }
    theEnemies.emplace_back(p);
    theTd.lock()->notifySpawn(p);
}

void Floor::spawnPotion(Type t, Info i) {
    // randomly spawn 1 potion
    if (i.x == -1) {
        i = randEmptyInfo();
    }
    shared_ptr<Potion> p;
    if (t == Type::rand) {
        shared_ptr<Potion> tmp = createPotion(i);
        p = tmp;
    } else if (t == Type::BA) {
        shared_ptr<Potion> tmp{new BA(i.x, i.y)};
        p = tmp;
    } else if (t == Type::BD) {
        shared_ptr<Potion> tmp{new BD(i.x, i.y)};
        p = tmp;
    } else if (t == Type::WA) {
        shared_ptr<Potion> tmp{new WA(i.x, i.y)};
        p = tmp;
    } else if (t == Type::WD) {
        shared_ptr<Potion> tmp{new WD(i.x, i.y)};
        p = tmp;
    } else if (t == Type::RH) {
        shared_ptr<Potion> tmp{new RH(i.x, i.y)};
        p = tmp;
    } else if (t == Type::PH) {
        shared_ptr<Potion> tmp{new PH(i.x, i.y)};
        p = tmp;
    }
    thePotions.emplace_back(p);
    theTd.lock()->notifySpawn(p);
}

void Floor::spawnTreasure(Type t, Info i) {
    // randomly spawn 1 treasure
    if (i.x == -1) {
        i = randEmptyInfo();
    }
    shared_ptr<Treasure> p;
    if (t == Type::rand) {
        shared_ptr<Treasure> tmp = createTreasure(i);
        p = tmp;
    } else if (t == Type::Small) {
        shared_ptr<Treasure> tmp{new Small(i.x,i.y)};
        p = tmp;
    } else if (t == Type::Normal) {
        shared_ptr<Treasure> tmp{new Normal(i.x,i.y)};
        p = tmp;
    } else if (t == Type::MerchantHoard) {
        shared_ptr<Treasure> tmp{new MerchantHoard(i.x,i.y)};
        p = tmp;
    } else if (t == Type::DragonHoard) {
        shared_ptr<Treasure> tmp{new DragonHoard(i.x,i.y)};
        p = tmp;
    }
        
    if (t == Type::rand && p->getType() == Type::DragonHoard) {
        while (!spawnDragon(p)) {
            p->setPos(randEmptyInfo());
        }
    }
    theTreasures.emplace_back(p);
    theTd.lock()->notifySpawn(p);
}

bool Floor::spawnDragon(shared_ptr<Treasure> theHoard) {
    Info dest = freeAround(theHoard->getPos());
    if (dest.x != -1) {
        shared_ptr<Enemy> dptr{new Dragon(theHoard, dest.x, dest.y)};
        theHoard->setDragon(dptr);
        theEnemies.emplace_back(dptr);
        theTd.lock()->notifySpawn(dptr);
        return true;
    } else {
        return false;
    }
}

void Floor::initTd(std::vector<std::vector<char>> aOrigTd, bool randGen, Type PCType) {
    // set chambercoords
    setChamberCoords(aOrigTd);
    
    // updates td and stdtd
    for (int y = 24; y >= 0; --y) {
        for (int x = 0; x <= 78; ++x) {
            if (aOrigTd[y][x] == '@') {
                // spawn PC at x, y with "PCType"
                spawnPC(PCType, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '\\') {
                spawnStair(Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '0') {
                spawnPotion(Type::RH, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '1') {
                spawnPotion(Type::BA, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '2') {
                spawnPotion(Type::BD, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '3') {
                spawnPotion(Type::PH, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '4') {
                spawnPotion(Type::WA, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '5') {
                spawnPotion(Type::WD, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '6') {
                spawnTreasure(Type::Normal, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '7') {
                spawnTreasure(Type::Small, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '8') {
                spawnTreasure(Type::MerchantHoard, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == '9') {
                spawnTreasure(Type::DragonHoard, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'H') {
                spawnEnemy(Type::Human, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'W') {
                spawnEnemy(Type::Dwarf, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'E') {
                spawnEnemy(Type::Elf, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'O') {
                spawnEnemy(Type::Orc, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'M') {
                spawnEnemy(Type::Merchant, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'D') {
                spawnEnemy(Type::Dragon, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else if (aOrigTd[y][x] == 'L') {
                spawnEnemy(Type::Halfling, Info(x,y));
                theTd.lock()->stdtd[y][x] = '.';
            } else {
                theTd.lock()->td[y][x] = aOrigTd[y][x];
                theTd.lock()->stdtd[y][x] = aOrigTd[y][x];
            }
        }
    }
    // all dragons need to find its hoard
    // all dragonhoards need to find its dragon
    // make sure all dragon can find its hoard
    bool allSet = false;
    while (!allSet) {
        allSet = true;
        random_shuffle(theTreasures.begin(),theTreasures.end());
        for (auto i : theEnemies) {
            if (i->getType() == Type::Dragon) {
                for (auto j : theTreasures) {
                    if (j->getType() == Type::DragonHoard) {
                        if (isClose(i->getPos(), j->getPos())) {
                            if (j->getDragon() == nullptr) {
                                i->setHoard(j);
                                j->setDragon(i);
                                break;
                            }
                        }
                    }
                }
            }
        }
        for (auto trea : theTreasures) {
            if (trea->getType() == Type::DragonHoard) {
                if (trea->getDragon() == nullptr) allSet = false;
            }
        }
        if (allSet == false) {
            for (auto trea : theTreasures) {
                if (trea->getType() == Type::DragonHoard) {
                    trea->setDragon(nullptr);
                }
            }
        }
        
    }
    
    if (randGen == true) {
        // generate all elements
        spawnPC(PCType);
        spawnStair();
        for (int i = 0; i < 10; i++) {
            spawnPotion();
        }
        for (int i = 0; i < 10; i++) {
            spawnTreasure();
        }
        for (int i = 0; i < 20; i++) {
            spawnEnemy();
        }
    }
    if (PCHP != 0) {
        myPC->modHP(INT_MIN);
        myPC->modHP(PCHP);
    }
    if (PCGold != 0) {
        myPC->modGold(-(myPC->getGold()));
        myPC->modGold(PCGold);
    }
}

void Floor::PCmove(Direction theDir) {
    // completes all actions, checks, msg for moving the PC
    Info dest = retDirInfo(myPC->getPos(), theDir);
    // goes to next level
    if (theTd.lock()->getChar(dest) == '\\') {
        if (LEVEL == 5) {
            if (myPC->getType() == Type::Shade) {
                SCORE = 1.5*(myPC->getGold());
            } else {
                SCORE = myPC->getGold();
            }
            throw GameStatus::Win;
        } else {
            PCHP = myPC->getHPVal();
            PCGold = myPC->getGold();
            myPC->rmEffect();
            incLevel();
            clearAllEPT();
            throw GameStatus::NextLevel;
        }
    }
    if (PCCanMove(dest)) {
        // troll gains 5 HP every turn
        if(myPC->getType() == Type::Troll) myPC->modHP(5);
        // track if there was a Treasure before Char move
        bool isTrea = (theTd.lock()->getChar(dest) == 'G');
        // PC moves to that place
        myPC->setPos(dest);
        // notify the td
        theTd.lock()->notifyPCMove();
        theTd.lock()->addPCMoveMsg(theDir);
        // use the Treasure if there is one
        if (isTrea) {
            useTreasure(dest);
        }
        // enemies attack PC if nearby
        attackPC();
    } else {
        TURN--;
        theTd.lock()->addInvalCmdMsg();
        return;
    }
    moveAllEnemy(TURN);
}

void Floor::attackPC() {
    // check if any enemy is close to PC's Info and attack (check hostile merchant and guarded DragonHoard)
    for(auto anEnemy : theEnemies) {
        // check if any enemy is close by
        if(isClose(myPC, anEnemy)) {
            // if Merchant, consider if Merchant is Hostile
            if (anEnemy->getType() == Type::Merchant) {
                if (Merchant::getHostile() == false) continue;
            }
            // attack PC if close
            anEnemy->attack(*myPC, TURN);
            theTd.lock()->addBeAttackMsg(anEnemy);
            if (anEnemy->getType() == Type::Elf && !(myPC->getType() == Type::Drow)) {
                anEnemy->attack(*myPC, TURN);
                theTd.lock()->addBeAttackMsg(anEnemy);
            }
            if (myPC->isDead()) {
                if (myPC->getType() == Type::Shade) {
                    SCORE = 1.5*(myPC->getGold());
                } else {
                    SCORE = myPC->getGold();
                }
                throw GameStatus::PCSlain;
            }
        }
    }
    for(auto anTreasure : theTreasures) {
        // if DragonHoard is close and guarded
        if (anTreasure->getType() == Type::DragonHoard) {
            if(isClose(myPC, anTreasure)) {
                if (anTreasure->guarded() == true) {
                    if (anTreasure->getDragon()->getTurn() != TURN) {
                        anTreasure->getDragon()->attack(*myPC, TURN);
                        theTd.lock()->addBeAttackMsg(anTreasure->getDragon());
                        if (myPC->isDead()) {
                            if (myPC->getType() == Type::Shade) {
                                SCORE = 1.5*(myPC->getGold());
                            } else {
                                SCORE = myPC->getGold();
                            }
                            throw GameStatus::PCSlain;
                        }
                    }
                }
            }
        }
    }
}

void Floor::attackEnemy(Direction theDir) {
    // completes all actions, checks, msg for attacking an enemy, called after command attack<Info>
    Info dest = retDirInfo(myPC->getPos(), theDir);
    shared_ptr<Enemy> tmp = getEnemy(dest);
    if (tmp == nullptr) {
        TURN--;
        theTd.lock()->addInvalCmdMsg();
        return;
    }
    // troll gains 5 HP every turn
    if(myPC->getType() == Type::Troll) myPC->modHP(5);
    myPC->attack(*tmp);
    theTd.lock()->addAttackMsg(tmp);
    if(myPC->isDead() == true) {
        if (myPC->getType() == Type::Shade) {
            SCORE = 1.5*(myPC->getGold());
        } else {
            SCORE = myPC->getGold();
        }
        throw GameStatus::PCAllergies;
    }
    if(tmp->isDead() == true) {
        detachEnemy(tmp->getPos());
        theTd.lock()->notifyDead(tmp);
        theTd.lock()->addSlayMsg(tmp);
        // generate Treasure if needed
        if (tmp->getType() == Type::Merchant) {
            shared_ptr<Treasure> p{new MerchantHoard(dest.x,dest.y)};
            theTreasures.emplace_back(p);
            theTd.lock()->notifySpawn(p);
            theTd.lock()->addSpawnMsg(p);
        }
        if (tmp->getType() == Type::Human) {
            shared_ptr<Treasure> p{new Normal(dest.x,dest.y,2)};
            theTreasures.emplace_back(p);
            theTd.lock()->notifySpawn(p);
            theTd.lock()->addSpawnMsg(p);
        }
        //detect if there's any DragonHoard below the PC
        if (tmp->getType() == Type::Dragon) {
            if (myPC->getPos() == tmp->getHoard()->getPos()) {
                useTreasure(tmp->getHoard()->getPos());
            }
        }
    }
    // attack PC
    attackPC();
    // move Enemies
    moveAllEnemy(TURN);
}

void Floor::attachEnemy(std::shared_ptr<Enemy> anNewEnemy) {
    // attaches Enemy to theEnemies
    theEnemies.emplace_back(anNewEnemy);
}

void Floor::detachEnemy(Info thePos) {
    // detaches Enemy from theEnemies at x, y
    for(auto anEnemyptr = theEnemies.begin(); anEnemyptr != theEnemies.end(); ++anEnemyptr) {
        if ((*anEnemyptr)->getPos() == thePos) {
            theEnemies.erase(anEnemyptr);
            break;
        }
    }
}

std::shared_ptr<Enemy> Floor::getEnemy(Info thePos) {
    // return the ptr to that Enemy at Info
    for (auto i : theEnemies) {
        if (i->getPos() == thePos) return i;
    }
    return nullptr;
}

bool sorty(std::shared_ptr<Enemy> e1, std::shared_ptr<Enemy> e2) {
    return e1->gety() > e2->gety();
}

void mybubbleSort(std::vector<std::shared_ptr<Enemy>>::iterator first, std::vector<std::shared_ptr<Enemy>>::iterator last) {
    std::vector<std::shared_ptr<Enemy>>::iterator i, j;
    for (i = first; i != last; i++) {
        for (j = first; j < i; j++) {
            if ((*i)->gety() == (*j)->gety()) {
                //
                if ((*i)->getx() < (*j)->getx()) {
                    std::iter_swap(i, j);
                }
            }
        }
    }
}


void mybubbleSort2(vector<Info>::iterator first, vector<Info>::iterator last, Info PCInfo) {
    vector<Info>::iterator i, j;
    for (i = first; i != last; i++) {
        for (j = first; j < i; j++) {
            // sqrt(pow(double((*i).x) - double(PCInfo.x), double(2)) + pow(double((*i).y) - double(PCInfo.y), double(2)))
            if (sqrt(pow(double((*i).x) - double(PCInfo.x), double(2)) + pow(double((*i).y) - double(PCInfo.y), double(2)))
                < sqrt(pow(double((*j).x) - double(PCInfo.x), double(2)) + pow(double((*j).y) - double(PCInfo.y), double(2))) ) {
                std::iter_swap(i, j);
            }
            
        }
    }
}

Info Floor::chasePC(Info aEnemy, Info thePC) {
    // returns a closest unoccupied Info to thePC
    map<Direction,int> tracker;
    while(true) {
        vector<Info> freeInfoLst;
        vector<Direction> dirList{Direction::no, Direction::so, Direction::ea, Direction::we, Direction::ne, Direction::nw, Direction::se, Direction::sw};
        for(auto aDir : dirList) {
            if (!(isOccupied(retDirInfo(aEnemy, aDir)))) {
                freeInfoLst.emplace_back(retDirInfo(aEnemy, aDir));
            }
        }
        if (freeInfoLst.size() == 0) return Info(-1,-1);
        mybubbleSort2(freeInfoLst.begin(), freeInfoLst.end(), thePC);
        return freeInfoLst[0];
    }
}

void Floor::moveAllEnemy(int curTurn) {
    if (FREEZE == true) return;
    // sort enemy so they move from top to bottem, left to right
        // sort y from 24 to 0
        // for each y, sort x from 0 to 78
    sort(theEnemies.begin(), theEnemies.end(), sorty);
    mybubbleSort(theEnemies.begin(), theEnemies.end());
    
    if (getDLC() == true) {
        // move all enemies that didn't attack
        for(auto anEnemyptr : theEnemies) {
            // if not attacked yet, will move
            if (anEnemyptr->getTurn() != curTurn && !(anEnemyptr->getType() == Type::Dragon)) {
                // get an unoccupied Info around the Enemy
                Info tmp(-1, -1);
                for (int i = 0; i < myChamberCoords.size(); i++) {
                    if (isInChamb(anEnemyptr->getPos(), i)) {
                        if (isInChamb(myPC->getPos(), i)) {
                            // if in the same chamber: chase
                            tmp = chasePC(anEnemyptr->getPos(), myPC->getPos());
                        } else {
                            // if not in the same chamber: not chase
                            tmp = freeAround(anEnemyptr->getPos());
                        }
                    }
                }
                if (tmp.x != -1) {
                    anEnemyptr->setPos(tmp);
                    anEnemyptr->setTurn(curTurn);
                    theTd.lock()->notifyMove(anEnemyptr);
                }
            }
        }
    } else {
        for(auto anEnemyptr : theEnemies) {
            // if not attacked yet, will move
            if (anEnemyptr->getTurn() != curTurn && !(anEnemyptr->getType() == Type::Dragon)) {
                // get an unoccupied Info around the Enemy
                Info tmp = freeAround(anEnemyptr->getPos());
                
                if (tmp.x != -1) {
                    anEnemyptr->setPos(tmp);
                    anEnemyptr->setTurn(curTurn);
                    theTd.lock()->notifyMove(anEnemyptr);
                }
            }
        }
    }
}

void Floor::attachPotion(std::shared_ptr<Potion> aNewPotion) {
    // attaches Potion to thePotions
    thePotions.emplace_back(aNewPotion);
}

void Floor::detachPotion(Info thePos) {
    // detaches Potion from thePotions at x, y
    for(auto aPotionptr = thePotions.begin(); aPotionptr != thePotions.end(); ++aPotionptr) {
        if ((*aPotionptr)->getPos() == thePos) {
            thePotions.erase(aPotionptr);
            break;
        }
    }
}

std::shared_ptr<Potion> Floor::getPotion(Info thePos) {
    // return the ptr to that Potion at Info
    for (auto i : thePotions) {
        if (i->getPos() == thePos) return i;
    }
    return nullptr;
}

void Floor::usePotion(Direction theDir) {
    // completes all actions, checks, msg for using a potion, called when command input use(Dir)
    Info dest = retDirInfo(myPC->getPos(), theDir);
    // if there is a potion
    if (theTd.lock()->getChar(dest) == 'P') {
        // troll gains 5 HP every turn
        if(myPC->getType() == Type::Troll) myPC->modHP(5);
        // find that potion
        shared_ptr<Potion> tmp = getPotion(dest);
        if (tmp->useMe(myPC) == true) {
            if (myPC->isDead() == true) {
                if (myPC->getType() == Type::Shade) {
                    SCORE = 1.5*(myPC->getGold());
                } else {
                    SCORE = myPC->getGold();
                }
                throw GameStatus::PCPoisoned;
            }
            detachPotion(dest);
            theTd.lock()->notifyDead(tmp);
            theTd.lock()->addUseMsg(tmp);
        }
    } else {
        --TURN;
        theTd.lock()->addInvalCmdMsg();
        return;
    }
    attackPC();
    moveAllEnemy(TURN);
}

void Floor::attachTreasure(std::shared_ptr<Treasure> aNewTreasure) {
    // attaches Treasure to theTreasures
    theTreasures.emplace_back(aNewTreasure);
}

void Floor::detachTreasure(Info thePos) {
    // detaches Treasure from theTreasures at x, y
    for(auto aTreaptr = theTreasures.begin(); aTreaptr != theTreasures.end(); ++aTreaptr) {
        if ((*aTreaptr)->getPos() == thePos) {
            theTreasures.erase(aTreaptr);
            break;
        }
    }
}

std::shared_ptr<Treasure> Floor::getTreasure(Info thePos) {
    // return the ptr to that Treasure at Info
    for (auto i : theTreasures) {
        if (i->getPos() == thePos) return i;
    }
    return nullptr;
}

void Floor::useTreasure(Info thePos) {
    // completes all actions, checks, msg for using a Treasure, called when command input walk on a Treasure
    shared_ptr<Treasure> tmp = getTreasure(thePos);
    if (tmp->useMe(myPC) == true) {
        detachTreasure(thePos);
        theTd.lock()->notifyDead(tmp);
        theTd.lock()->addUseMsg(tmp);
    } else {
        theTd.lock()->addNotUseMsg(tmp);
    }
}

bool Floor::isOccupied(Info thePos) {
    // returns true if Info is currently occupied
    if (theTd.lock()->getChar(thePos) == '.') return false;
    return true;
}

void Floor::clearAllEPT() {
    theEnemies.clear();
    thePotions.clear();
    theTreasures.clear();
    myChamberCoords.clear();
}

Info Floor::freeAround(Info thePos) {
    // returns an unoccupied Info around thePos
    Info toBeRet(-1, -1);
    map<Direction,int> tracker;
    while(true) {
        // if no place to go, return (-1, -1)
        if (tracker.size() == 8) return toBeRet;
        int i = rand() % 8 + 1;
        if (i == 1) {
            if (isOccupied(retDirInfo(thePos, Direction::no))) {
                tracker[Direction::no];
            } else {
                return retDirInfo(thePos, Direction::no);
            }
        } else if (i == 2) {
            if (isOccupied(retDirInfo(thePos, Direction::so))) {
                tracker[Direction::so];
            } else {
                return retDirInfo(thePos, Direction::so);
            }
        } else if (i == 3) {
            if (isOccupied(retDirInfo(thePos, Direction::ea))) {
                tracker[Direction::ea];
            } else {
                return retDirInfo(thePos, Direction::ea);
            }
        } else if (i == 4) {
            if (isOccupied(retDirInfo(thePos, Direction::we))) {
                tracker[Direction::we];
            } else {
                return retDirInfo(thePos, Direction::we);
            }
        }  else if (i == 5) {
            if (isOccupied(retDirInfo(thePos, Direction::ne))) {
                tracker[Direction::ne];
            } else {
                return retDirInfo(thePos, Direction::ne);
            }
        } else if (i == 6) {
            if (isOccupied(retDirInfo(thePos, Direction::nw))) {
                tracker[Direction::nw];
            } else {
                return retDirInfo(thePos, Direction::nw);
            }
        } else if (i == 7) {
            if (isOccupied(retDirInfo(thePos, Direction::se))) {
                tracker[Direction::se];
            } else {
                return retDirInfo(thePos, Direction::se);
            }
        } else {
            if (isOccupied(retDirInfo(thePos, Direction::sw))) {
                tracker[Direction::sw];
            } else {
                return retDirInfo(thePos, Direction::sw);
            }
        }
    }
}


bool Floor::PCCanMove(Info thePos) {
    // returns true if PC can move onto that Info
    char destChar = theTd.lock()->getChar(thePos);
    // chars that PC can walk on
    if ((destChar == '.') || (destChar == '+') ||
        (destChar == '#') || (destChar == 'G') ||
        (destChar == '\\')) {
        return true;
    } else {
        return false;
    }
    
}

Info Floor::randEmptyInfo() {
    // returns a randomly selected Info in ChamberNum
    while(true) {
        int randChamberNum = rand() % myChamberCoords.size();
        for (int i = 0; i < myChamberCoords.size(); i++) {
            if (i == randChamberNum) {
                int InfoNum = rand() % myChamberCoords[randChamberNum].size();
                if (!(isOccupied(myChamberCoords[randChamberNum][InfoNum]))) return (myChamberCoords[randChamberNum][InfoNum]);
            }
        }
    }
}

bool Floor::isInChamb(Info theInfo, int ChamberNum) {
    //returns true if Info is in ChamberNum
    for (int i = 0; i < myChamberCoords[ChamberNum].size(); ++i) {
        if (theInfo == myChamberCoords[ChamberNum][i]) return true;
    }
    return false;
}

// Helper for setChamberCoords. check if c is in aVec
bool isInVec(char c, vector<char> aVec) {
    for (auto aChar : aVec) {
        if (c == aChar) return true;
    }
    return false;
}

// Helper for setChamberCoords. return a vector of valid Char around an Info
vector<Info> findAllValCharAround(Info aInfo, vector<vector<char>> aOrigMap, vector<vector<bool>> aBoolVec) {
    vector<Direction> dirVec{Direction::no, Direction::so, Direction::ea, Direction::we};
    vector<char> validChar{'@', '\\', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'H', 'W', 'E', 'O', 'M', 'D', 'L', '.'};
    vector<Info> toBeRet;
    
    for (auto aDir : dirVec) {
        Info tmp = retDirInfo(aInfo, aDir);
        if (tmp.x >= 0 && tmp.x < aOrigMap[0].size()
            && tmp.y >= 0 && tmp.y < aOrigMap.size()
            && isInVec(aOrigMap[tmp.y][tmp.x], validChar)
            && aBoolVec[tmp.y][tmp.x] == false) {
            toBeRet.emplace_back(tmp);
        }
    }
    return toBeRet;
}

void Floor::setChamberCoords(std::vector<std::vector<char>> aOrigFloor) {
    // updates ChamberCoords
    
    // initialize a boolCharts to track if x,y is in a chamber
    vector<vector<bool>> InChart;
    vector<bool> tmpFalse;
    for(int i = 0; i <= 78; ++i) {
        tmpFalse.emplace_back(false);
    }
    for (int j = 24; j >= 0; --j) {
        InChart.emplace_back(tmpFalse);
    }
    
    // initialize a boolChart to track if x,y has been used to check
    vector<vector<bool>> CheckChart;
    for (int j = 24; j >= 0; --j) {
        CheckChart.emplace_back(tmpFalse);
    }
    
    
    // still have more?
    bool MoreChamb = true;
    // chamber starts with 0
    int ChamberNum = -1;
    // validChar
    vector<char> validChar{'@', '\\', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'H', 'W', 'E', 'O', 'M', 'D', 'L', '.'};
    
    // find one validChar and expand around it
    while (MoreChamb) {
        MoreChamb = false; // if no valid char is found, end
        for (int y = 24; y >= 0; y--) {
            for (int x = 0; x <= 78; x++) {
                // if an unused validChar is found
                if (InChart[y][x] == false && isInVec(aOrigFloor[y][x], validChar)) {
                    ChamberNum++;
                    MoreChamb = true; // inidicates more chambs is possible
                    InChart[y][x] = true; // corresponding boolChart becomes true
                    myChamberCoords.emplace_back();
                    myChamberCoords[ChamberNum].emplace_back(Info(x,y));
                    bool MoreChar = true;
                    while (MoreChar) {
                        MoreChar = false;
                        for (auto aInfo : myChamberCoords[ChamberNum]) {
                            if (CheckChart[aInfo.y][aInfo.x] == false) {
                                CheckChart[aInfo.y][aInfo.x] = true;
                                vector<Info> aListOfValidInfo = findAllValCharAround(aInfo, aOrigFloor, InChart);
                                if (aListOfValidInfo.size() != 0) {
                                    MoreChar = true;
                                    for (auto aValidInfo : aListOfValidInfo) {
                                        InChart[aValidInfo.y][aValidInfo.x] = true;
                                        myChamberCoords[ChamberNum].emplace_back(aValidInfo);
                                        
                                    }
                                } else {
                                    continue;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}



// ctor
Floor::Floor(std::shared_ptr<TextDisplay> theTd) : theTd{theTd} {}

bool isClose(Info pos1, Info pos2) {
    // if x, y are 1 radius close, then they are close
    if ((abs(pos1.x - pos2.x) <= 1) && (abs(pos1.y - pos2.y) <= 1)) return true;
    return false;
}

bool isClose(std::shared_ptr<Base> Base1, std::shared_ptr<Base> Base2) {
    // calls isClose(Info, Info)
    return isClose(Base1->getPos(), Base2->getPos());
}
