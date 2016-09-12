#pragma once

#include "core/Node/InterfaceNode.h"
#include "core/Node/Node.h"

#include <vector>

using namespace std;

class InterfaceNode: public Node
{
public:
    InterfaceNode(): Node() {}

    void prepareToFire();
	void fire();

    bool isPreparedToFire;
    
};
