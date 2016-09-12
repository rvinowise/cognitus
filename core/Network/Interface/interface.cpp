#include "Interface.h"

Interface::Interface()
{

}

void Interface::initNodes(int inQty) {
    for (int i_node = 0; i_node < inQty; i_node++) {
        node.push_back(new InterfaceNode());
    }
}

void Interface::firePreparedNodes()
{
    for (int i_node = 0; i_node < node.size(); i_node++) {
        if (node[i_node]->isPreparedToFire) {
            node[i_node]->fire();
        }
    }
}
