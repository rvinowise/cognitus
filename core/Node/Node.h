#pragma once

#include <vector>

namespace core {

class LineOfCircuit;
class Circuit;
class Bend;
class Node_data;

class Node
{
friend class InterfaceNode;
public:
    Node();
    Node(const Node& other);
    Node(Node&& other);
    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    Node(Circuit inCircuit);
    void incorporate_circuit_to_this_node(Circuit inCircuit);

    virtual void fire();

    bool isLowest();
    Bend add_bend();
    Bend get_lower_chain_bend();
private:
    Node_data* data;

    void add_new_bend_as_active();  
    void carefully_preserve_initial_chain_because_of_its_context(LineOfCircuit inLine, Bend first_chain_bend, Bend second_chain_bend);
};


}
