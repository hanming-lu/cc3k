#include "Direction.h"

Direction operator!(std::string t) {
    if (t == "no") return Direction::no;
    if (t == "so") return Direction::so;
    if (t == "ea") return Direction::ea;
    if (t == "we") return Direction::we;
    if (t == "ne") return Direction::ne;
    if (t == "nw") return Direction::nw;
    if (t == "se") return Direction::se;
    if (t == "sw") return Direction::sw;
    return Direction::wrong;
}
