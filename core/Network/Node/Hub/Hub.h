#pragma once

#include <memory>
#include <vector>

#include "core/Network/Link/Linked.h"

/// @image html position2.png

namespace core {

class Node;
class Node_data;
class Bend;
class Hub_data;
using std::size_t;
class Hub: public Linked
{
public:
    Hub();
    Hub(Node in_figure_node);
    Hub(Node_data in_figure_node_data);
    Hub(const Hub &other);
    ~Hub();
    static Hub new_empty();
    bool is_empty();

    bool operator==(const Hub& other) const;
    bool operator!=(const Hub& other)const;
    Hub& operator=(const Hub& other);

    size_t get_prev_links_qty() const;
    size_t get_next_links_qty() const;
    Hub get_next(size_t index);
    Hub get_prev(size_t index);
    std::vector<Hub>& get_arr_next_figures();

    Node get_node_of_whole_figure();
    bool is_this_last_bend_in_chain() const;
    Hub add_next_bend();
    void push_next_bend(Hub in_figure);
    std::vector<Bend>& get_arr_free_bends();

#ifdef debug_mode
    void letdown_new_bends_to_node(size_t qty, Node node);
    std::vector<Hub> get_arr_not_linked_hubs(std::vector<Hub> hubs);
    bool lead_to(Hub other);
#endif

private:


    Hub_data* data;

};


}
