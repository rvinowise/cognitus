#include "Node.h"
#include "Node_data.h"

#include "core/Network/Network.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/test/allTests.h"
#endif

namespace core {

Node::Node()
{
    data = new Node_data;

}

Node::Node(const Node &other)
{
    data = other.data;
}

Node::Node(Node &&other)
{
    data = other.data;
}

Node& Node::operator=(const Node &other)
{
    data = other.data;
    return *this;
}

bool Node::operator==(const Node &other) const
{
    return data==other.data;
}

Node::Node(Circuit inCircuit)
{

}

void Node::fire()
{
    add_new_bend_as_active();
}



void Node::add_new_bend_as_active() {
    Bend newBend(*this);
    data->bend.push_back(newBend);
    network->save_new_activated_bend(newBend);
}


bool Node::isLowest()
{
    return data->lowerChainBend.isEmpty();
}


}
