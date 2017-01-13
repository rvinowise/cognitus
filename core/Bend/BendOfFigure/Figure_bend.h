#pragma once

#include "core/Bend/Bend.h"

/// @image html position2.png

namespace core {

class Figure_bend: Linked
{
public:
    Figure_bend();

    Node& get_node_of_whole_figure();

    bool is_this_last_bend_in_chain() const;
private:
    // essential
    Node nodeOfWholeFigure;
    std::vector<Bend> freeBend;

};


}
