#ifndef TextDisplay_h
#define TextDisplay_h
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ncurses.h>
#include "Type.h"
#include "Info.h"

class Base;
class PC;
class Enemy;
class Potion;
class Treasure;
class Floor;

class TextDisplay {
    std::weak_ptr<Floor> myFloor;
    
    std::weak_ptr<PC> myPC;
    std::string msg;
    std::vector<std::vector<char>> stdtd;
    std::vector<std::vector<char>> td;
    
    WINDOW * curwin;

public:
// print out the window
// DLC
    void windowPrint(); // print using window
    void setWindow(WINDOW *); // set the window to print
    WINDOW *getWindow(); // get the window to print
    
// modify td
    void updateFloor(std::shared_ptr<Floor>); // updates myFloor
    
    void notifyPCSpawn(std::shared_ptr<PC>); // set the PC's ptr
    void notifySpawn(std::shared_ptr<Base>); // update the spawn td
    void notifySpawn(char, Info); // spawn the stair
    
    void notifyPCMove(); // update the before and after locations, (check if any treasure is in that x, y), print msg
    void notifyMove(std::shared_ptr<Enemy>); // update the before and after locations, print msg
    
    void notifyDead(std::shared_ptr<Base>); // if not Treasure, update the location char, print msg based on type
    char getChar(Info); // return the Char on td at Info
    
// modify msg
    void addMsg(std::string); // add msg to msg
    void addPCMoveMsg(Direction); // add PC move message
    void addAttackMsg(std::shared_ptr<Enemy>); // add an Attack Msg
    void addBeAttackMsg(std::shared_ptr<Enemy>); // add a beattacked Msg
    void addSlayMsg(std::shared_ptr<Enemy>); // add a slaying and gold gain Msg
    void addSpawnMsg(std::shared_ptr<Base>); // add a spawn msg
    void addUseMsg(std::shared_ptr<Potion>); // add a Potion use and effect Msg
    void addUseMsg(std::shared_ptr<Treasure>); // add a Treasure use and gold gain Msg
    void addInvalCmdMsg(); // add invalid command msg
    void addNotUseMsg(std::shared_ptr<Treasure>); // add a Treasure not used no gold gain Msg
    void clearMsg(); // clears msg in the beginning of each turn
    
    TextDisplay(); // ctor
    
    friend class Floor;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td); // need to access private field
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td); // print out the tb map, with status and msg
#endif
