
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

void Bend::transmitExpectationForward()
{
    if (isThisLastBendInChain()) {
        highNode->fire();
    } else {
        transmitExpectationHorisontal();
    }
    firedBend.clear(); //?
}

bool Bend::isThisLastBendInChain() {
    return nextBend.size() == 0;
}


void Bend::transmitExpectationHorisontal() {
    for (unsigned int i_bend=0; i_bend<nextBend.size(); i_bend++) {
        //expect(nextBend[i_bend]);
        nextBend[i_bend]->expectedBy(this);
    }
}


void Bend::expectedBy(Bend* expectingBend) {
    firedBend.insert(expectingBend);
    if ((isExpectedByAll()) && (!node->isLowest())) {
        node->expectLowerBends();
    }
}

void Bend::connectTo(Bend *toBend)
{
    this->nextBend.push_back(toBend);
    toBend->prevBend.push_back(this);
}



bool Bend::isExpectedByAll()
{
    return firedBend.size() == prevBend.size();
}

