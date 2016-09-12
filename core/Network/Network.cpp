#include "Network.h"

Network network;


Network::Network()
{

}

void Network::step()
{
    fireInputAndThenHigherNodes();
    connectLastBendsToNewOnes();
    createNewHighNodes();
}


void Network::fireInputAndThenHigherNodes() {
    input.firePreparedNodes();
}

void Network::connectLastBendsToNewOnes() {
    lastActiveBend.connectThisBendsToOthers(&newActiveBend);
    lastActiveBend = newActiveBend;
    newActiveBend.bend.clear();
}

void Network::createNewHighNodes()
{

}



void Network::saveNewActivatedBend(Bend *inBend)
{
    newActiveBend.bend.push_back(inBend);
}


