
#include "Bend.h"

#include "core/Node/Node.h"

Bend::Bend(Node *masterNode)
{
    node = masterNode;
    node->bend.push_back(this);
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
    //return nextBend == nullptr;
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
    /*this->nextBend = toBend;
    toBend->prevBend.push_back(this);*/
}




