#pragma once


#include <vector>
#include <set>
#include <memory>

#include "core/Network/Link/Linked.h"

#ifdef rendering_mode
#include "interface/drawable_units/draw_Bend.h"
#endif


namespace core {


typedef std::size_t Moment;

struct Activation_interval
{
public:
    Activation_interval() = default;
    Activation_interval(Moment moment):
        start{moment}, end{moment}{}
    Activation_interval(Moment in_start, Moment in_end):
        start{in_start}, end{in_end}{}
    Moment when_does_the_bend_becomes_active() {return start;}
    Moment when_does_the_bend_turns_off() {return end;}

    Moment start;
    Moment end;
};


class Bend_data;
class Node;
class Hub;
class Sequence_pair;

class Bend: public Linked
#ifdef rendering_mode
        ,public render::Bend
#endif
{
friend struct std::hash<core::Bend>;
public:
    Bend();
    Bend(Activation_interval interval);
    Bend(Node &masterNode, std::size_t index_in_master_node);
    Bend incorporate_line_to_this_bend(Sequence_pair in_line);
    Bend(const Bend& other);
    Bend(Bend&& other);
    
    ~Bend();
    Bend& operator=(const Bend& other);
    bool operator==(const Bend& other) const;
    bool operator!=(const Bend& other) const;


    bool is_empty() const;

    Node& get_master_node();
    const Node& get_master_node() const;
    std::size_t get_index_in_master_node() const;

    std::size_t get_prev_links_qty() const;
    std::size_t get_next_links_qty() const;
    Bend get_prev_bend(std::size_t index) const;
    Bend get_next_bend(std::size_t index) const;
    Bend get_prev_brother_bend() const;

    const std::vector<core::Bend>& prev_bends() const;
    std::vector<core::Bend>& next_bends();
    const std::vector<core::Bend>& next_bends() const;

    std::size_t get_higher_nodes_qty() const;
    Node get_higher_node(std::size_t index) const;
    std::vector<Node> get_common_higher_nodes_with(Bend otherBend);
    std::vector<Hub> &hubs();


    void append_to_higher_node(Node& inNode);
    void copy_prev_bends_from(Bend otherBend);
    void copy_next_bends_from(Bend otherBend);
    void attach_to_hub(Hub hub);
    void connect_to(Bend& toBend);
    

    void deallocate_all_connected_entities_upward();
    void remove();
    
    bool executed_before_this(Bend in_bend) const;
    bool executed_after_this(Bend in_bend) const;
    Activation_interval interval();
    void set_interval(Activation_interval in_interval);

protected:
    void erase_next_bend(std::size_t index);
    void erase_prev_bend(std::size_t index);

private:
    Bend_data* data;

};


}


namespace std {
  template <> struct hash<core::Bend>
  {
    size_t operator()(const core::Bend& bend) const
    {
      return hash<std::size_t>()(
                  reinterpret_cast<std::size_t>(bend.data)
                  );
    }
  };
}
