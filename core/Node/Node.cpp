#include "Node.h"

#include "core/Network/Network.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/test/alltests.h"
#endif

namespace core {

void Node::fire()
{
#ifdef debug_mode
    if (
            core::input_iteration != test::i_iteration
            ) {
        bool errorCatched = true;
    }
#endif
    add_new_bend_as_active();

    //createNewAndExpandOldFigures();
    //createHighNodes();
}



void Node::add_new_bend_as_active() {
    Bend* newBend = new Bend(this);
    bend.push_back(newBend);
    network->save_new_activated_bend(newBend);
}


bool Node::isLowest()
{
    return (lowerChainBend == nullptr);
}

void Node::expectLowerBends()
{
    lowerChainBend->fire();
}

}
