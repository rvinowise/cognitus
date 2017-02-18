#pragma once

#include <memory>
#include <vector>
//#include <>

#include "core/Network/Link/Linked.h"

#ifdef render_mode
#include "interface/drawable_units/draw_Hub.h"
#endif

/// @image html position2.png


namespace core {


class Node;
class Node_data;
class Bend;
class Hub_data;
using std::size_t;

class Hub: public Linked
#ifdef render_mode
        ,public render::Hub
#endif
{
friend struct std::hash<core::Hub>;
public:
    Hub();
    Hub(Node in_figure_node);
    Hub(const Hub &other);
    ~Hub();
    void create_data();
    static Hub new_empty();
    bool is_empty();

    bool operator==(const Hub& other) const;
    bool operator!=(const Hub& other)const;
    Hub& operator=(const Hub& other);

    size_t get_prev_links_qty() const;
    size_t get_next_links_qty() const;
    Hub get_next(size_t index);
    Hub get_prev(size_t index);
    std::vector<core::Hub>& get_arr_next_hubs() const;

    Node get_node_of_whole_figure();
    bool is_this_last_bend_in_chain() const;
    Hub add_next_hub();
    void push_next_hub(Hub in_hub);
    std::vector<Bend>& get_arr_free_bends();

#ifdef debug_mode
    void letdown_new_bends_to_node(size_t qty, Node node);
    std::vector<Hub> get_hubs_leading_to_this();
    std::vector<Hub> get_hubs_possible_for_linking(std::vector<Hub> hubs);
    bool lead_to(Hub other);
#endif

private:


    Hub_data* data;

};


}

namespace std {
  template <> struct hash<core::Hub>
  {
    size_t operator()(const core::Hub& hub) const
    {
      return hash<std::size_t>()(
                  reinterpret_cast<std::size_t>(hub.data)
                  );
    }
  };
}
