#pragma once

#include "core/Network/Node/Bend/Bend.h"

namespace core {

class Bend;

struct Sequence_pair
{
public:
    Sequence_pair() {}
    Sequence_pair(Bend start_bend, Bend end_bend):
        data{start_bend, end_bend}{}
    bool is_has_noise_bends_inside();
    Bend start(){return data.start;}
    Bend end() {return data.end;}
    Activation_interval interval();

private:
    struct Data {
        Bend start;
        Bend end;
    } data;
};

class Node;

class Circuit
{
public:
    Circuit();
    Circuit(const Circuit& other) = default;
    Circuit(Circuit&& other) = default;
    Circuit(const Sequence_pair& prev_line, const Sequence_pair& last_line):
        first_sequence{prev_line}, last_sequence{last_line}{}

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


    Sequence_pair get_first_line();
    Sequence_pair get_second_line();
private:
    Sequence_pair first_sequence;
    Sequence_pair last_sequence;
};

}
