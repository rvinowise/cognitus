#pragma once

#include "Bend.h"
#include "core/Node/Node.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"
#include "Figure_bend/Figure_bend.h"

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


class Bend_data: public Acquiring_handles
{
public:
    Bend_data(Node& masterNode);

    std::vector<Bend> prev_bends;
    std::vector<Bend> next_bends;
    Node& master_node;
    std::vector<Figure_bend> higher_figure_bends;
    Activation_interval interval;
};


}
