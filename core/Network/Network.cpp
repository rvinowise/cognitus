#include "Network.h"

Network network;


Network::Network()
{

}

/*void Network::initProcessingThreads()
{
    //threadProcessInput = new std::thread(checkAndProcessInputSignals);
}*/

void Network::step() {

    prepareOutputOnMotors();

}

/*void Network::checkAndProcessInputSignals() {
    if (areInputSignalsChanged()) {

        constructCurrentStructureOfNodes();
    }
}*/

void Network::constructCurrentStructureOfNodes() {

    registerActivationOfExistingNodes();
    extendNodesAndCreateNewOnes();
}

void Network::connectLastBendsToNewOnes() {
    lastActiveBends.connectThisBendsToOthers(&newActiveBends);
    lastActiveBends = newActiveBends;
    newActiveBends.bend.clear();
}

void Network::registerActivationOfExistingNodes() {

}

void Network::extendNodesAndCreateNewOnes() {
    //Circuits circuits = findCircuits(newActiveBends);
    //extendNodesAndCreateNewOnes(circuits);
}





void Network::createNewHighNodes()
{

}



void Network::saveNewActivatedBend(Bend *inBend)
{
    newActiveBends.bend.push_back(inBend);
}


void Network::prepareOutputOnMotors() {

}


