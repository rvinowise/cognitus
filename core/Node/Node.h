#pragma once

#include <vector>

namespace core {

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

    virtual void fire();

    bool isLowest();

private:
    Node_data* data;

    void add_new_bend_as_active();  
};


}
