#pragma once

#include "core/Bend/Bend.h"
#include "core/Node/Node.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Node_data;

class Figure_bend_data: public Acquiring_handles
{
public:
    Figure_bend_data();
    Figure_bend_data(Node in_figure_node);
    Figure_bend_data(Node_data in_figure_node_data);

    std::vector<Figure_bend> prev_bends;
    std::vector<Figure_bend> next_bends;

    Node figure_node;
    std::vector<Bend> free_bends;
};


}
