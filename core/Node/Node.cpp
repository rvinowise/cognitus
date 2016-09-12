#include "Node.h"

#include "core/Network/Network.h"

void Node::fire()
{
    transmitExpectationForward();
    addNewActiveBend();

    //createHighNodes();
}



void Node::transmitExpectationForward()
{
    for (unsigned int i=0;i<bend.size();i++) {
        if (bend[i]->isExpectedByAll()) {
            bend[i]->transmitExpectationForward();
        }
    }
}


void Node::addNewActiveBend() {
    Bend* newBend = new Bend(this);
    bend.push_back(newBend);
    network.saveNewActivatedBend(newBend);
}


bool Node::isLowest()
{
    return (lowerChainBend == nullptr);
}

void Node::expectLowerBends()
{
    lowerChainBend->transmitExpectationForward();
}
