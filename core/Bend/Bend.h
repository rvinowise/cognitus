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

struct Place_in_node
{
public:
    Place_in_node() {};
    Node node;
};

class Bend_data
{
public:
    Bend_data() {}
    //Bend_data(const Bend_data& other) = default;

    std::vector<Bend> prevBend;
    std::vector<Bend> nextBend;
    Node node;
    std::vector<Place_in_node> place_in_node;
    Activation_interval interval;


private:
    std::set<Bend> firedBend;
};

class Bend
{
public:
    Bend();
    Bend(Node masterNode);
    Bend(const Bend& other);
    Bend(Bend&& other);
    ~Bend();
    Bend& operator=(const Bend& other);
    bool operator==(const Bend& other) const;

    bool is_this_last_bend_in_chain() const;
    void connect_to(Bend& toBend);
    bool isEmpty() const;
    Node getNode();

    std::size_t get_prev_bends_qty() const;
    std::size_t get_next_bends_qty() const;
    Bend get_prev_bend(std::size_t index) const;
    Bend get_next_bend(std::size_t index) const;

    std::size_t get_higher_nodes_qty() const;
    Node get_higher_node(std::size_t index) const;
    std::vector<Node> get_common_higher_nodes_with(Bend otherBend);



    const std::vector<Bend>& get_array_of_prev_bends() const;
    const std::vector<Bend>& get_array_of_next_bends() const;

private:
    Bend_data* data;

#ifdef debug_mode
    std::size_t indexInput;
#endif
};


}
