#include "InterfaceNode.h"

#include "core/Network/network.h"

#include <algorithm>

namespace core {


InterfaceNode::InterfaceNode()
    :Node()
{
    isPreparedToFire = false;
}

void InterfaceNode::prepareToFire() {
	isPreparedToFire = true;
}

void InterfaceNode::fire() {
	isPreparedToFire = false;
    Node::fire();
}

size_t InterfaceNode::get_index_in_interface_array()
{
    return index_in_interface_array;
}

}
