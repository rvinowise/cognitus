#pragma once

#include "core/Bend/Bend.h"

namespace core {

struct LineOfCircuit
{
    Bend start;
    Bend end;
};

class Node;

class Circuit
{
public:
    Circuit();

    Bend getFirstStartBend();
    Bend getSecondStartBend();
    Bend getFirstEndBend();
    Bend getSecondEndBend();

    void putFirstStartBend(Bend);
    void putSecondStartBend(Bend);
    void putFirstEndBend(Bend);
    void putSecondEndBend(Bend);
    bool is_first_consequence_placed_inside_one_higher_node();
    Node create_higher_node_for_it();
private:
    LineOfCircuit firstLine;
    LineOfCircuit secondLine;
};

}
