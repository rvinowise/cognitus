#pragma once

#include "core/Node/InterfaceNode.h"

#include <vector>


namespace core {

class Network;

class Interface
{
public:
    Interface(Network& inNetwork);

    void initNodes(std::size_t inQty);
    std::size_t getNodesQty();

    void deallocate_all_connected_entities();
    InterfaceNode getNode(std::size_t index);

    std::vector<InterfaceNode>::iterator begin();
    std::vector<InterfaceNode>::iterator end();
protected:
    void firePreparedNodes();
    void prepareToFire(int index);
    bool isPreparedToFire(int index);
    Network& network;

private:
    std::vector<InterfaceNode> node;    
	
};

}
