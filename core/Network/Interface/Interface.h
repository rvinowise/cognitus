#pragma once

#include "core/Node/InterfaceNode.h"

#include <vector>


namespace core {

class Interface
{
public:
	Interface();

    void initNodes(std::size_t inQty);
    std::size_t getNodesQty();

    void deallocate_all_connected_entities();
protected:
    void firePreparedNodes();
    void prepareToFire(int index);
    bool isPreparedToFire(int index);

private:
    std::vector<InterfaceNode> node;
	
};

}
