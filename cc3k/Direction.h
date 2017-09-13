#ifndef Direction_h
#define Direction_h
#include <string>

// Direction for the user input
enum class Direction {
    no, so, ea, we, ne, nw, se, sw, wrong,
    tp
};

Direction operator!(std::string t);
#endif
