// by a58zhang, h65lu, y842liu for CS246 1175 Final Project
// This file is contributed by Hanming Lu (h65lu)
#ifndef Info_h
#define Info_h
#include "Direction.h"

// provides the x, y coordinates using a Info
struct Info {
    int x;
    int y;
    Info(int x, int y);
};

// define ==
bool operator==(Info i1, Info i2);

// return the direction Info
Info retDirInfo(Info i, Direction theDir);


#endif
