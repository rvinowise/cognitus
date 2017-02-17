#pragma once

#include "Bend.h"
#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"

namespace core {

typedef std::size_t Input_iteration;

struct Activation_interval
{
public:
    Input_iteration when_does_the_bend_becomes_active() {return start;}
    Input_iteration when_does_the_bend_turns_off() {return end;}

    Input_iteration start;
    Input_iteration end;
};


class Bend_data
{
public:
    Bend_data(Node& masterNode);

    std::vector<Bend> prev_bends;
    std::vector<Bend> next_bends;
    Node& master_node;
    std::size_t index_in_master_node;
    std::vector<Hub> higher_hubs;
    Activation_interval interval;
};


}
