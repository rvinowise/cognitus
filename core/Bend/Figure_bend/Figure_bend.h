#pragma once

#include <memory>
#include <vector>

#include "core/Bend/Link/Linked.h"

/// @image html position2.png

namespace core {

class Node;
class Node_data;
class Bend;
class Figure_bend_data;
using std::size_t;
class Figure_bend: public Linked
{
public:
    Figure_bend();
    Figure_bend(Node in_figure_node);
    Figure_bend(Node_data in_figure_node_data);
    Figure_bend(const Figure_bend &other);
    ~Figure_bend();
    static Figure_bend new_empty();
    bool is_empty();

    bool operator==(const Figure_bend& other) const;
    bool operator!=(const Figure_bend& other)const;
    Figure_bend& operator=(const Figure_bend& other);

    size_t get_prev_links_qty() const;
    size_t get_next_links_qty() const;
    Figure_bend get_next(size_t index);
    Figure_bend get_prev(size_t index);
    std::vector<Figure_bend>& get_arr_next_figures();

    Node& get_node_of_whole_figure();   
    bool is_this_last_bend_in_chain() const;
    Figure_bend add_next_bend();
    void push_next_bend(Figure_bend in_figure);
    std::vector<Bend>& get_arr_free_bends();

#ifdef debug_mode
    void letdown_new_bends_to_node(size_t qty, Node node);
    std::vector<Figure_bend> get_arr_not_linked_figures(std::vector<Figure_bend> figures);
    bool lead_to(Figure_bend other);
#endif

private:


    Figure_bend_data* data;

};


}
