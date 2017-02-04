#pragma once

#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Node.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Node_data;

class Hub_data: public Acquiring_handles
{
public:
    Hub_data();
    Hub_data(Node in_figure_node);
    Hub_data(Node_data in_figure_node_data);

    std::vector<Hub> prev_hubs;
    std::vector<Hub> next_hubs;

    Node figure_node;
    std::vector<Bend> free_bends;
};


}
