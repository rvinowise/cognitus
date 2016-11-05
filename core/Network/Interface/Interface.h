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

protected:
    void firePreparedNodes();
    void prepareToFire(int index);

private:
    std::vector<InterfaceNode*> node;
	
};

}
