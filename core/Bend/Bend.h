#pragma once


#include <vector>
#include <set>
#include <memory>

#include "core/Node/Node.h"

namespace core {

class Bend;


typedef std::size_t Input_iteration;

struct Activation_interval
{
public:
    Input_iteration when_does_the_bend_becomes_active() {return start;}
    Input_iteration when_does_the_bend_turns_off() {return end;}

    Input_iteration start;
    Input_iteration end;
};

/*struct Place_in_node
{
public:
    Place_in_node() {};
    is_start_of_node();
    is_end_of_node();
private:
    Bend bend;
};*/

class Bend_data
{
public:
    Bend_data(Node& masterNode);

    //common
    std::vector<Bend> prevBend;
    std::vector<Bend> nextBend;
    Node& master_node;
    Activation_interval interval;

    // bend_of_figure
    Node node_of_whole_figure;

    // free_bend
    std::vector<Bend> higher_figure_bends;

private:
    std::set<Bend> firedBend;
};

class Bend
{
public:
    Bend();
    Bend(Node &masterNode);
    Bend(const Bend& other);
    Bend(Bend&& other);
    ~Bend();
    Bend& operator=(const Bend& other);
    bool operator==(const Bend& other) const;
    bool operator!=(const Bend& other) const;


    void remove();

    bool is_this_last_bend_in_chain() const;
    void connect_to(Bend& toBend);
    bool is_empty() const;
    Node& get_master_node();
    Node& get_node_of_whole_figure();

    std::size_t get_prev_bends_qty() const;
    std::size_t get_next_bends_qty() const;
    Bend get_prev_bend(std::size_t index) const;
    Bend get_next_bend(std::size_t index) const;

    std::size_t get_higher_nodes_qty() const;
    Node get_higher_node(std::size_t index) const;
    std::vector<Node> get_common_higher_nodes_with(Bend otherBend);

    void append_to_higher_node(Node& inNode);
    void copy_prev_bends_from(Bend otherBend);
    void copy_next_bends_from(Bend otherBend);
    void attach_to_bend_of_figure(Bend figureBend);
    Bend add_next_bend();

    const std::vector<Bend>& get_array_of_prev_bends() const;
    const std::vector<Bend>& get_array_of_next_bends() const;

protected:
    void erase_next_bend(std::size_t index);
    void erase_prev_bend(std::size_t index);

private:
    Bend_data* data;

#ifdef debug_mode
    std::size_t indexInput;
#endif
};


}
