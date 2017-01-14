#pragma once

#include <memory>

#include "core/Bend/Link/Linked.h"

/// @image html position2.png

namespace core {

class Node;
class Bend;
class Figure_bend_data;

class Figure_bend: public Linked
{
public:
    Figure_bend();
    ~Figure_bend();

    std::size_t get_prev_links_qty() const;
    std::size_t get_next_links_qty() const;

    Node& get_node_of_whole_figure();   
    bool is_this_last_bend_in_chain() const;
    Figure_bend add_next_bend();

private:


    Figure_bend_data* data;

};


}
