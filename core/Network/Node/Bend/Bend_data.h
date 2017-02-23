#pragma once

#include "Bend.h"
#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"

namespace core {


class Bend_data
{
public:
    Bend_data(Node& masterNode);

    std::vector<Bend> prev_bends;
    std::vector<Bend> next_bends;
    Node master_node;
    std::size_t index_in_master_node;
    std::vector<Hub> higher_hubs;
    Activation_interval interval;
};


}
