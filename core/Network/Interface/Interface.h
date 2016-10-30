#pragma once

#include "core/Node/InterfaceNode.h"

#include <vector>


namespace core {

class Interface
{
friend class Network;
public:
	Interface();

    void initNodes(int inQty);
    void prepareToFire(int index);
    std::size_t getNodesQty();
    std::vector<InterfaceNode*> node;
protected:
    void firePreparedNodes();

private:

	
};

}
