#include "Node.h"

#include "core/Network/Network.h"

void Node::fire()
{
    transmitExpectationForward();
    addNewBendAsActive();

    //createNewAndExpandOldFigures();
    //createHighNodes();
}



void Node::transmitExpectationForward()
{
    /*for (unsigned int i=0;i<bend.size();i++) {
        if (bend[i]->isExpected) {
            bend[i]->fire();
        }
    }*/
}


void Node::addNewBendAsActive() {
    /*Bend* newBend = new Bend(this);
    network.saveNewActivatedBend(newBend);*/
}


bool Node::isLowest()
{
    return (lowerChainBend == nullptr);
}

void Node::expectLowerBends()
{
    lowerChainBend->fire();
}
