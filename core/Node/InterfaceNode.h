#pragma once

#include "core/Node/InterfaceNode.h"
#include "core/Node/Node.h"

#include <vector>

namespace core {

class InterfaceNode: public Node
{
public:
    InterfaceNode();

    void prepareToFire();
	void fire();



    bool isPreparedToFire;
    
    std::size_t get_index_in_interface_array();
    std::size_t index_in_interface_array;
};


}
