
#include "Bend.h"

#include "core/Node/Node.h"

#ifdef debug_mode
#include "core/Node/InterfaceNode.h"
#include "core/Network/Network.h"
#include "core/test/alltests.h"
#endif

namespace core {

Bend::Bend(Node *masterNode)
{
    node = masterNode;
#ifdef debug_mode
    indexInput = static_cast<InterfaceNode*>(masterNode)->get_index_in_interface_array();
#endif
}

/*void Bend::expectedFire()
{
    transmitExpectationForward();
}*/

void Bend::fire()
{
    /*if (isThisLastBendInChain()) {
        highNode->fire();
    } else {
        expectLastBend();
    }
    isExpected = false;*/
}

bool Bend::isThisLastBendInChain() {
    return nextBend.empty();
}


/*void Bend::expectLastBend() {
    //nextBend[i_bend]->expect();
}


void Bend::expect() {
    isExpected = true;
    if (!node->isLowest()) {
        node->expectLowerBends();
    }
}*/



void Bend::connectTo(Bend *toBend)
{
    this->nextBend.push_back(toBend);
    toBend->prevBend.push_back(this);
}

}


