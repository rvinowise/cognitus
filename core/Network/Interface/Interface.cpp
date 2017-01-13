#include "Interface.h"

#ifdef debug_mode
#include "core/test/allTests.h"
#endif

namespace core {


Interface::Interface()
{

}

void Interface::initNodes(std::size_t inQty) {
    for (std::size_t i_node = 0; i_node < inQty; i_node++) {
        InterfaceNode newInterfaceNode;
        newInterfaceNode.set_index_in_interface_array(node.size());
        node.push_back(newInterfaceNode);
    }
}

void Interface::firePreparedNodes()
{
    for (size_t i_node = 0; i_node < node.size(); i_node++) {
        if (node[i_node].is_prepared_to_fire()) {
            node[i_node].fire();
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
        node.deallocate_all_connected_entities();
    }
}


}
