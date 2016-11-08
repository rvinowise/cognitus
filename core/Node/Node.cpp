#include "Node.h"

#include "core/Network/Network.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/test/allTests.h"
#endif

namespace core {

void Node::fire()
{
    add_new_bend_as_active();

    //createNewAndExpandOldFigures();
    //createHighNodes();
}



void Node::add_new_bend_as_active() {
    Bend newBend(*this);
    bend.push_back(newBend);
    network->save_new_activated_bend(newBend); //error
}


bool Node::isLowest()
{
    return lowerChainBend.isEmpty();
}

void Node::expectLowerBends()
{

}

}
