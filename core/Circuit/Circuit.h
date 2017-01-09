#pragma once

#include "core/Bend/Bend.h"

namespace core {

struct LineOfCircuit
{
public:
    LineOfCircuit() {}
    bool is_has_noise_bends_inside();
    Bend get_start(){return start;}
    Bend get_end() {return end;}

    Bend start;
    Bend end;
};

class Node;

class Circuit
{
public:
    Circuit();
    Circuit(const Circuit& other) = default;
    Circuit(Circuit&& other) = default;

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
    bool is_complete();


    LineOfCircuit get_first_line();
    LineOfCircuit get_second_line();
private:
    LineOfCircuit firstLine;
    LineOfCircuit secondLine;
};

}
