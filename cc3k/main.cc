#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <ncurses.h>
#include "GameStatus.h"
#include "Floor.h"
#include "TextDisplay.h"
#include "Type.h"
#include "Direction.h"
#include "Merchant.h"
#include "PC.h"
using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    while(true) {
        // initiate a new game
        bool RANDGEN = false; // if random generation is not needed, change to false
        Merchant::setHostile(false);// Merchant is initially not hostile
        
        // initiate floor and Td
        shared_ptr<TextDisplay> myTd{new TextDisplay()};
        shared_ptr<Floor> myFloor{new Floor(myTd)};
        myTd->updateFloor(myFloor);
        
        // set DLC to true if needed
        cout << "Use DLC? (Y/N)" << endl;
        string s0;
        cin >> s0;
        if (s0 == "Y") myFloor->setDLC(true);
    
        
        // 1 for loop initialize theStdtd
        vector<vector<char>> theStdtd;
        for (int i = 0; i <= 24; ++i) {
            theStdtd.emplace_back();
        }
        
        // 5 for loops initialize theTds
        vector<vector<vector<char>>> theTds;
        for (int i = 0; i < 5; ++i) {
            theTds.emplace_back();
            for (int j = 0; j <= 24; ++j) {
                theTds[i].emplace_back();
            }
        }
        
        if (argc > 2) {
            cerr << "Incorrect amount of command line arguments. Usage: ./program mapname" << endl;
            return 1;
        } else if (argc == 2) {
            // read in the map in its original state
            ifstream iff(argv[1]);
            if (iff.fail()) {
                cerr << "Incorrect map name, please enter an existing map. Usage: ./program mapname" << endl;
                return 1;
            }
            char c;
            for (int i = 0; i < 5; ++i) {
                for (int row = 24; row >= 0; --row) {
                    for (int col = 0; col <= 78; ++col) {
                        iff.get(c);
                        if(iff.fail()) {
                            cerr << "Incorrect map content.";
                            return 1;
                        }
                        if (c == '\n') {
                            --col;
                            continue;
                        }
                        theTds[i][row].emplace_back(c);
                    }
                }
            }
            // detect if random generation is needed
            RANDGEN = true;
            for (int row = 24; row >= 0; --row) {
                for (int col = 0; col <= 78; ++col) {
                    if (theTds[0][row][col] == '@') {
                        RANDGEN = false;
                        break;
                    }
                }
                if (RANDGEN == false) break;
            }
        } else {
            // Empty default map is used
            RANDGEN = true;
            // 1 for loop read default.txt into theStdtd
            ifstream iff1("default.txt");
            if(iff1.fail()) {
                cerr << "default.txt required." << endl;
                return 1;
            }
            char c1;
            for (int row = 24; row >= 0; --row) {
                for (int col = 0; col <= 78; ++col) {
                    iff1.get(c1);
                    if(iff1.fail()) {
                        cout << "Incorrect Default.txt content." << endl;
                        return 1;
                    }
                    if (c1 == '\n') {
                        --col;
                        continue;
                    }
                    theStdtd[row].emplace_back(c1);
                }
            }
            iff1.close();

            // read default.txt into theTds
            for (int i = 0; i< 5; ++i) {
                for (int row = 24; row >= 0; --row) {
                    for (int col = 0; col <= 78; ++col) {
                        theTds[i][row].emplace_back(theStdtd[row][col]);
                    }
                }
            }
        }
        
        // get PCType
        cout << "Please choose one of the following PC races: 's' - Shade(default), 'd' - Drow, 'v' - Vampire, 'g' - Goblin, 't' - Troll. ";
        if (myFloor->getDLC() == true) {
            cout << "DLC: 'sp' - SuperMan, or 'rand' - random.";
        }
        cout << endl;
        string s2;
        cin >> s2;
        Type PCType = *(s2);
        if (PCType == Type::SuperMan && myFloor->getDLC() == false) {
            PCType = Type::Shade;
        }
        if (PCType == Type::rand && myFloor->getDLC() == false) {
            PCType = Type::Shade;
        }
        if (PCType == Type::rand && s2 != "rand") {
            PCType = Type::Shade;
        }
        
        try {
            if (myFloor->getDLC() == false) {
                while(true) {
                    // initiate a new level
                    // update td, stdtd, chamberCoords with PC Type
                    myFloor->initTd(theTds[(myFloor->getLevel())-1], RANDGEN, PCType);
                    
                    try {
                        while (true) {
                            // initiate a turn
                            // Turn ++
                            myFloor->incTurn();
                            cout << *myTd;
                            // clear Msg
                            myTd->clearMsg();
                            cout << "Please enter exactly one of the following user commands as below: \"<direction>\", \"u <direction>\", \"a <direction>\", \"f\", \"r\", \"q\", where <direction> can be one of: no, so, ea, we, ne, nw, se, sw.";
                            if (myFloor->getDLC() == true && myFloor->getMyPC()->getType() == Type::SuperMan) {
                                cout << "\"t x y\", where x, y is a valid position in the map. ";
                            }
                            cout<< endl;
                            // read in and call corresponding floor methods
                            string cmd;
                            cin >> cmd;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore();
                                myFloor->quitGame();
                            }
                            if (cmd == "a") {
                                string dir;
                                cin >> dir;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore();
                                    continue;
                                }
                                if (!dir == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->attackEnemy(!dir);
                            } else if(cmd == "u") {
                                string dir;
                                cin >> dir;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore();
                                    continue;
                                }
                                if (!dir == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->usePotion(!dir);
                            } else if (cmd == "f") {
                                myFloor->toggleFreeze();
                                continue;
                            } else if (cmd == "r") {
                                myFloor->RestartGame();
                            } else if (cmd == "q") {
                                myFloor->quitGame();
                            } else if (cmd == "+") {
                                myFloor->cheatHP();
                            } else if (cmd == "t" && myFloor->getDLC() == true && myFloor->getMyPC()->getType() == Type::SuperMan) {
                                int x1;
                                int y1;
                                cin >> x1;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore();
                                    continue;
                                }
                                cin >> y1;
                                if (cin.fail()) {
                                    cin.clear();
                                    cin.ignore();
                                    continue;
                                }
                                myFloor->teleport(x1,y1);
                            } else {
                                if (!cmd == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->PCmove(!cmd);
                            }
                        }
                    } catch (GameStatus theStatus) {
                        if (theStatus == GameStatus::NextLevel) {
                            myTd->addMsg("You have enhanced to the next level, you are currently on level " + to_string(myFloor->getLevel()) + ".");
                            continue;
                        } else {
                            throw;
                        }
                    } catch (...) {}
                }
            } else {
                // use Window WASD display
                // ncurses start
                initscr();
                noecho();
                cbreak();
                
                // get screen size
                int yMax, xMax;
                getmaxyx(stdscr, yMax, xMax);
                
                // create a window for our input
                WINDOW * playwin = newwin(40, 80, 0, 0);
                refresh();
                wrefresh(playwin);
                
                // setWindow
                myTd->setWindow(playwin);
                
                keypad(playwin, true);

                while(true) {
                    // initiate a new level
                    // update td, stdtd, chamberCoords with PC Type
                    myFloor->initTd(theTds[(myFloor->getLevel())-1], RANDGEN, PCType);
                    try {
                        while (true) {
                            // initiate a turn
                            // Turn ++
                            myFloor->incTurn();
                            // print on the window
                            myTd->windowPrint();
                            // clear Msg
                            myTd->clearMsg();
                            // y=33, x = 0
                            if (myFloor->getDLC() == true && myFloor->getMyPC() ->getType() == Type::SuperMan) {
                                mvwprintw(myTd->getWindow(), 33, 0, "Please press exactly one of the following user commands as below: \"<direction>\", \"u <direction>\", \"a <direction>\", \"f\", \"r\", \"q\", where <direction> can be one of: LEFT, RIGHT, UP, DOWN. Or \"t x [space] y [ENTER] \", where x, y is a valid position in the map.");
                            } else {
                                mvwprintw(myTd->getWindow(), 33, 0, "Please press exactly one of the following user commands as below: \"<direction>\", \"u <direction>\", \"a <direction>\", \"f\", \"r\", \"q\", where <direction> can be one of: LEFT Key, RIGHT Key, UP Key, DOWN Key.");                            }
                            
                            // read in and call corresponding floor methods
                            // read in a cmd
                            int cmd = wgetch(playwin);
                            if (cmd == 'a') {
                                // get direction
                                int dirChar = wgetch(playwin);
                                string dir;
                                switch (dirChar) {
                                    case KEY_UP:
                                        dir = "no";
                                        break;
                                    case KEY_DOWN:
                                        dir = "so";
                                        break;
                                    case KEY_LEFT:
                                        dir = "we";
                                        break;
                                    case KEY_RIGHT:
                                        dir = "ea";
                                        break;
                                    default:
                                        dir = "wrong";
                                        break;
                                }
                                if (!dir == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->attackEnemy(!dir);
                            } else if(cmd == 'u') {
                                // get direction
                                int dirChar = wgetch(playwin);
                                string dir;
                                switch (dirChar) {
                                    case KEY_UP:
                                        dir = "no";
                                        break;
                                    case KEY_DOWN:
                                        dir = "so";
                                        break;
                                    case KEY_LEFT:
                                        dir = "we";
                                        break;
                                    case KEY_RIGHT:
                                        dir = "ea";
                                        break;
                                    default:
                                        dir = "wrong";
                                        break;
                                }
                                if (!dir == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->usePotion(!dir);
                            } else if (cmd == 'f') {
                                myFloor->toggleFreeze();
                                continue;
                            } else if (cmd == 'r') {
                                myFloor->RestartGame();
                            } else if (cmd == 'q') {
                                myFloor->quitGame();
                            } else if (cmd == '+') {
                                myFloor->cheatHP();
                            } else if (cmd == 't' && myFloor->getDLC() == true && myFloor->getMyPC()->getType() == Type::SuperMan) {
                                string xCoord = "";
                                string yCoord = "";
                                while (true) {
                                    int xDig = wgetch(playwin);
                                    if (xDig >= '0' && xDig <= '9') {
                                        string aDig = to_string(xDig - '0');
                                        xCoord += aDig;
                                    } else {
                                        break;
                                    }
                                }
                                while (true) {
                                    int yDig = wgetch(playwin);
                                    if (yDig >= '0' && yDig <= '9') {
                                        string aDig = to_string(yDig - '0');
                                        yCoord += aDig;
                                    } else {
                                        break;
                                    }
                                }
                                int x1;
                                int y1;
                                if (xCoord == "" || yCoord == "") {
                                    x1 = -1;
                                    y1 = -1;
                                } else {
                                    x1 = stoi(xCoord);
                                    y1 = stoi(yCoord);
                                }
                                myFloor->teleport(x1,y1);
                            } else {
                                string dir;
                                switch (cmd) {
                                    case KEY_UP:
                                        dir = "no";
                                        break;
                                    case KEY_DOWN:
                                        dir = "so";
                                        break;
                                    case KEY_LEFT:
                                        dir = "we";
                                        break;
                                    case KEY_RIGHT:
                                        dir = "ea";
                                        break;
                                    default:
                                        dir = "wrong";
                                        break;
                                }
                                if (!dir == Direction::wrong) {
                                    myTd->addInvalCmdMsg();
                                    continue;
                                }
                                myFloor->PCmove(!dir);
                            }
                        }
                    } catch (GameStatus theStatus) {
                        if (theStatus == GameStatus::NextLevel) {
                            myTd->addMsg("You have enhanced to the next level, you are currently on level " + to_string(myFloor->getLevel()) + ".");
                            continue;
                        } else {
                            throw;
                        }
                    } catch (...) {}
                }
            }
        } catch (GameStatus theStatus) {
            // close window when needed
            if (myFloor->getDLC() == true) {
                endwin();
            }
            string ctn;
            if (theStatus == GameStatus::Win) {
                cout << "Congrats! You have won the game with a score of: " << myFloor->getScore() << ", Well done!" << endl;
            } else if (theStatus == GameStatus::Quit) {
                cout << "Keep it up! Try again! Your score is: " << myFloor->getScore() << endl;
                break;
            } else if (theStatus == GameStatus::Restart) {
                ctn = "Y";
            } else if (theStatus == GameStatus::PCSlain) {
                cout << "Unfortunately, you have been slain. Your score is: " << myFloor->getScore() << endl;
            } else if (theStatus == GameStatus::PCPoisoned) {
                cout << "Unfortunately, you have been poinsoned. Your score is: " << myFloor->getScore() << endl;
            } else if (theStatus == GameStatus::PCAllergies) {
                cout << "Unfortunately, you are dead to allergies. Your score is: " << myFloor->getScore() << endl;
            }
            if (ctn != "Y") {
                cout<< "Restart? (Y, N)" << endl;
                cin >> ctn;
                if(cin.fail()) break;
            }
            if (ctn == "Y") {
                continue;
            } else {
                break;
            }
        }
    }
}
        // construct the stdtd, read in a map (store PC's Info, randomly decide Potion and Treasure type), store the first floor in td,
                // give user choices of PC race
                // create a flag to ask user if rand generate is needed
                // if spawn is needed, spawn PC, stair (not in the same chamber as PC, using ChamberInfo), generate 10 potions, 10 gold, and 20 enemies using chamberInfo, check not occupied , put them into thePotions, theTreasures, theEnemies
                    // check if DragonHoard is spawn, if yes, create a Dragon beside it, and pass DragonHoard's address to the Dragon ctor, pass Dragon's ptr to theDragonHoard
                // set PC to td
        
        // every floor (while loop)
            // level ++
            // repeat everything in game start, except for PC race choice
        
        // Every Turn
            // Turn++
            // character moves first
                // if move.
                    // check if destination is occupied using theEnemies, thePotions.
                        // if yes, ignore
                        // if no, check if that is a valid place through Chambers, passages, doors. move to that destination (update x, y, update td, msg display). check if destination is a stair, if yes, check current level, goes to next level or end game (break) with success msg, delete everything. check if destination is occupied by a Treasure using theTreasures
                            // If yes, calls that Treasure's useMe(), if returns true, call that Treasure's dtor, rm it from theTreasures, msg display. If false, no action.
                            // if no, no action
                    // check if the original place is occupied by a Treasure using theTreasures,
                        // if yes, change the display to G
                        // if no, change the display to the char from stdtb
                    // check if character's surrounding has an Enemy using floor's theEnemies, or DragonHoard with isGuarded == true,
                        // if yes, check if Merchant,
                            // if yes, check if Hostile. if yes, call Enemy's attack on the PC, msg display
                            // if no, call Enemy's attack on the PC, msg display
                    // check if PC dies
                        // if yes, goes to end a game, send out msg that PC is slain
                // if use.
                    // check if destination is occupied using thePotions
                        // if yes, call useMe on that Potion, call that Potion's dtor, rm it from thePotions, update td, msg display. check if PC is dead.
                            // if yes, goes to end a game, send out msg that PC is poisoned to death
                            // if no, ignore
                        // if no, ignore
                // if attack.
                    // check if destination is an Enemy from theEnemy.
                        // if yes, call PC's attack on that Enemy, msg display. check if PC's dead
                            // if yes, goes to end a game, msg: <PC> dead to allergy to <Enemy>
                            // if no, check if Enemy is dead
                                // if yes, call dtor on that Enemy, rm it from theEnemies, update td, msg display
                                // if no, ignore
                        // if no, ignore
                // if "f".
                    // set Freeze = true
                // if "r".
                    // goes to restart game
                // if "q"
                    // goes to end a game, pass a msg
        
            // Enemies move next.
                // if Freeze == true, ignore
                // for each enemy in theEmemies, check if Type == Dragon, if yes, ignore. check if Enemy's turn != Turn
                    // if yes, check if there's a valid space around it
                        // if yes, rand an x, y, check if x,y is not the original place or occupied by any of PC, theEnemies, thePotions, or theTreasures
                            // if yes, call Enemy.setPos(x, y), update td, original place is ".", break
                            // if no, enters while loop
                        // if no, ignore, Enemy's turn++
                    // if no, ignore
        
        // end a game
            // pass a msg from above, display a score using PC's gold, delete everything
        
        // restart a game
            // delete everything and continue

