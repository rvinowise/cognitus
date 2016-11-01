#include "Network.h"

#include <QtDebug>

#ifdef debug_mode
#include "core/test/alltests.h"
#include <atomic>
#endif

namespace core {


#ifdef debug_mode
    std::atomic_size_t input_iteration;
#endif

Network *network;


Network::Network()
{
    lastActiveBends = new ActiveBends();

}

/*void Network::initProcessingThreads()
{
    //threadProcessInput = new std::thread(checkAndProcessInputSignals);
}*/

void Network::step() {

    prepareOutputOnMotors();

}

ActiveBends* Network::getLastActiveBends()
{
    return lastActiveBends;
}


void Network::constructCurrentStructureOfNodes() {

    registerActivationOfExistingNodes();
    extendNodesAndCreateNewOnes();
}

#ifdef debug_mode
extern std::atomic_size_t input_iteration;
#endif

void Network::prepare_to_new_input_iteration()
{
#ifdef debug_mode
    input_iteration.store(test::i_iteration);
#endif
    newActiveBends = new ActiveBends();
}

void Network::connect_last_bends_to_new_ones() {
    if (!newActiveBends->bend.empty()) {
        lastActiveBends->connectThisBendsToOthers(newActiveBends);
        delete lastActiveBends;
        lastActiveBends = newActiveBends;
    } else {
        delete newActiveBends;
    }
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



void Network::save_new_activated_bend(Bend *inBend)
{
    newActiveBends->bend.push_back(inBend);
}


void Network::prepareOutputOnMotors() {

}


}


