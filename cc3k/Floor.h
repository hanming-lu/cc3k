#ifndef Floor_h
#define Floor_h
#include <vector>
#include <memory>
#include "Info.h"
#include "Direction.h"
#include "Type.h"

class Base;
class Enemy;
class Potion;
class Treasure;
class PC;
class TextDisplay;

class Floor {
    int PCHP = 0;
    int PCGold = 0;
    bool FREEZE = false;
    bool myDLC = false;

    int TURN = 0;
    int LEVEL = 1;
    int SCORE = 0;

    std::shared_ptr<PC> myPC;
    std::weak_ptr<TextDisplay> theTd;
    std::vector<std::shared_ptr<Enemy>> theEnemies;
    std::vector<std::shared_ptr<Potion>> thePotions;
    std::vector<std::shared_ptr<Treasure>> theTreasures;
    std::vector<std::vector<Info>> myChamberCoords;

public:
// get field
    int getLevel(); // return level
    int getScore(); // return Score
    bool getDLC(); // return myDLC
    void setDLC(bool); // return myDLC
    std::shared_ptr<PC> getMyPC(); // return myPC
    
// user input calls from main
    void usePotion(Direction); // completes all actions, checks, msg for using a potion, called when command input use(Info)
    void PCmove(Direction); // completes all actions, checks, msg for moving the PC
    void attackEnemy(Direction); // completes all actions, checks, msg for attacking an enemy, called after command attack<Info>
    void cheatHP(); // increases HP by 1000 for testing
    void teleport(int x, int y); // teleport to pos x, y
    void toggleFreeze(); // toggle Freeze
    void quitGame(); // throw a Quit Game status
    void RestartGame(); // throw a restart game status
     
// System calls from main
    void incTurn(); // increase TURN by 1
    void incLevel(); // increase level by 1
    void spawnPC(Type t = Type::rand, Info i = Info(-1,-1)); // spawns the PC at Info, randomly if info(-1,-1)
    void spawnStair(Info i = Info(-1,-1)); // spawn 1 Stair at Info, randomly if info(-1,-1)
    void spawnEnemy(Type t = Type::rand, Info i = Info(-1,-1)); // spawn 1 Type enemy at Info, randomly if info(-1,-1)
    void spawnPotion(Type t = Type::rand, Info i = Info(-1,-1)); // spawn 1 Type potion at Info, randomly if info(-1,-1)
    void spawnTreasure(Type t = Type::rand, Info i = Info(-1,-1)); // spawn 1 Type treasure at Info, randomly if info(-1,-1)
    void initTd(std::vector<std::vector<char>> aOrigTd, bool,Type PCType = Type::rand); // construct the display Td using a OrigTd, calls all spawn methods if original map has any,
    void setChamberCoords(std::vector<std::vector<char>>); // updates ChamberCoords

// Helpers
    void attackPC(); // check if any enemy is close to PC's Info and attack (check hostile merchant and guarded DragonHoard)
    
    void detachGeneral(std::shared_ptr<Base>); // detaches any of Enemy, Potion, or Treasure
    
    void attachEnemy(std::shared_ptr<Enemy> aNewEnemy); // attaches Enemy to theEnemies
    void detachEnemy(Info); // detaches Enemy from theEnemies at x, y
    std::shared_ptr<Enemy> getEnemy(Info); // return the ptr to that Enemy at Info
    void moveAllEnemy(int curTurn); // move all enemies that didn't attack
    
    void attachPotion(std::shared_ptr<Potion> aNewPotion); // attaches Potion to thePotions
    void detachPotion(Info); // detaches Potion from thePotions at x, y
    std::shared_ptr<Potion> getPotion(Info); // return the ptr to that Enemy at Info
    
    void attachTreasure(std::shared_ptr<Treasure> aNewTreasure); // attaches Treasure to theTreasures
    void detachTreasure(Info); // detaches Treasure from theTreasures at x, y
    std::shared_ptr<Treasure> getTreasure(Info); // return the ptr to that Enemy at Info
    void useTreasure(Info); // completes all actions, checks, msg for using a Treasure, called when command input walk on a Treasure
    
    bool spawnDragon(std::shared_ptr<Treasure> theHoard); // generate the Dragon beside the Hoard, return false if no space beside the Hoard
    bool isOccupied(Info); // returns true if Info is currently occupied
    Info freeAround(Info); // returns an unoccupied Info around thePos, if no unoccupied Info around, return (-1, -1)
    Info chasePC(Info aEnemy, Info thePC); // 
    bool PCCanMove(Info); // returns true if PC can move onto that Info
    
    void clearAllEPT(); // clears all theEnemies/thePotions/theTreasures
    Info randEmptyInfo(); // returns a randomly selected Info in ChamberNum
    
    bool isInChamb(Info, int ChamberNum);
    
    Floor(std::shared_ptr<TextDisplay> theTd); // ctor
    
    friend bool sorty(std::shared_ptr<Enemy>, std::shared_ptr<Enemy>);
    friend void mybubbleSort(std::vector<std::shared_ptr<Enemy>>::iterator first, std::vector<std::shared_ptr<Enemy>>::iterator last);
    friend bool isClose(Info pos1, Info pos2); // may access private field
    friend bool isClose(std::shared_ptr<Base> Base1, std::shared_ptr<Base> Base2); // may access private field
};

bool sorty(std::shared_ptr<Enemy>, std::shared_ptr<Enemy>); // sort y in descending order
void mybubbleSort(std::vector<std::shared_ptr<Enemy>>::iterator first, std::vector<std::shared_ptr<Enemy>>::iterator last);


bool isClose(Info pos1, Info pos2); // returns true if pos1 is close to pos2
bool isClose(std::shared_ptr<Base> Base1, std::shared_ptr<Base> Base2); // returns true if pos1 is close to pos2
#endif
