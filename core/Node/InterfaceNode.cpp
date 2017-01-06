#include "InterfaceNode.h"

#include "core/Network/Network.h"

#include <algorithm>

namespace core {


InterfaceNode_data::InterfaceNode_data()
{
    is_prepared_to_fire = false;
}


InterfaceNode::InterfaceNode()
    :Node()
{
    interface_data = new InterfaceNode_data();
}

InterfaceNode::InterfaceNode(const Node &other)
    :Node(other)
{
    interface_data = new InterfaceNode_data();
}
InterfaceNode::InterfaceNode(const InterfaceNode &other)
    :Node(other)
{
    interface_data = other.interface_data;
}

void InterfaceNode::prepare_to_fire() {
    interface_data->is_prepared_to_fire = true;
}
bool InterfaceNode::is_prepared_to_fire() {
    return interface_data->is_prepared_to_fire;
}

void InterfaceNode::fire() {
    interface_data->is_prepared_to_fire = false;
    Node::fire();
}

void InterfaceNode::set_index_in_interface_array(std::size_t index)
{
    interface_data->index_in_interface_array = index;
}

std::size_t InterfaceNode::get_index_in_interface_array() const
{
    return interface_data->index_in_interface_array;
}



}
