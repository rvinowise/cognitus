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
    Figure_bend get_lower_chain_bend();
private:
    Node_data* data;

    void add_new_bend_as_active();  
    void carefully_preserve_initial_chain_because_of_its_context(
            LineOfCircuit inLine, Figure_bend first_chain_bend, Figure_bend second_chain_bend);
};


}
