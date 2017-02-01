#pragma once

#include <vector>



namespace core {

class LineOfCircuit;
class Circuit;
class Bend;
class Figure_bend;
class Node_data;

class Node
{
friend class InterfaceNode;
public:
    Node();
    Node(Node_data &in_node_data);
    Node(Circuit inCircuit);
    Node(const Node& other);
    Node(Node&& other);
    ~Node();
    void deallocate_with_all_connected_entities_upward();

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;


    void incorporate_circuit_to_this_node(Circuit inCircuit);

    virtual void fire();

    bool isLowest();
    Bend add_bend();
    void append_bend(const Bend& bend);
    std::vector<Figure_bend>& get_arr_figure_bends();
    Figure_bend add_figure_bend();

    std::vector<Bend> &bends();

    class iterator_BFS;
    iterator_BFS begin();
    iterator_BFS end();
    typedef Figure_bend value_type;

#ifdef debug_mode
    bool has_it_as_progeny(Node node);
    bool is_progeny_of(Node node);
    void generate_random_empty_figure(std::size_t figure_size);
#endif

    //Figure_bend figure
private:
    Node_data* data;

    void add_new_bend_as_active();  
    void carefully_preserve_initial_chain_because_of_its_context(
            LineOfCircuit inLine, Figure_bend first_chain_bend, Figure_bend second_chain_bend);
};


}
