#include "Interface.h"

#include "core/test/Debug_inspector.h"
#include "core/Network/Network.h"


namespace core {

using std::size_t;

Interface::Interface(Network &inNetwork):
    network{inNetwork}
{

}

void Interface::initNodes(std::size_t inQty) {
    for (std::size_t i_node = 0; i_node < inQty; i_node++) {
        InterfaceNode newInterfaceNode;
        newInterfaceNode.create_data();
        newInterfaceNode.set_index_in_interface_array(node.size());
        node.push_back(newInterfaceNode);
    }
}

void Interface::firePreparedNodes()
{
    for (size_t i_node = 0; i_node < node.size(); i_node++) {
        if (node[i_node].is_prepared_to_fire()) {
            network.fire_node(node[i_node]);
        }
    }
}


void Interface::prepareToFire(int index)
{
    node[index].prepare_to_fire();
}

bool Interface::isPreparedToFire(int index)
{
    return node[index].is_prepared_to_fire();
}

std::size_t Interface::getNodesQty()
{
    return node.size();
}

void Interface::deallocate_all_connected_entities()
{
    for (auto node: this->node ) {
        //node.deallocate_all_connected_entities();

    }
}

InterfaceNode Interface::getNode(std::size_t index)
{
    if (node.size() <= index) {
        throw_msg("Interface::getNode out of range");
    }
    return node[index];
}

std::vector<InterfaceNode>::iterator Interface::begin()
{
    return node.begin();
}
std::vector<InterfaceNode>::iterator Interface::end()
{
    return node.end();
}


}
