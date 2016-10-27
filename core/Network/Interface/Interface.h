#pragma once

#include "core/Node/InterfaceNode.h"

#include <vector>

using namespace std;



class Interface
{
friend class Network;
public:
	Interface();

    void initNodes(int inQty);
    void firePreparedNodes();

    vector<InterfaceNode*> node;
	
private:

	
};

