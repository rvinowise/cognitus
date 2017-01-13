#include "Network.h"

#include <QtDebug>

#ifdef debug_mode
#include "core/test/allTests.h"
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

Network::~Network()
{
    deallocate_all_entities_of_network();
}

void Network::deallocate_all_entities_of_network()
{
    input.deallocate_all_connected_entities();
    output.deallocate_all_connected_entities();
}


void Network::step() {

    prepareOutputOnMotors();

}

ActiveBends& Network::getLastActiveBends()
{
    return *lastActiveBends;
}



void Network::prepare_to_new_input_iteration()
{
    newActiveBends = new ActiveBends();
}

void Network::save_new_activated_bend(Bend inBend)
{
    newActiveBends->bend.push_back(inBend);
}

void Network::prolongate_history_of_inputs() {
    // incapsulate?
    if (!newActiveBends->bend.empty()) {
        lastActiveBends->connect_this_bends_to_others(*newActiveBends);
        delete lastActiveBends;
        lastActiveBends = newActiveBends;
    } else {
        delete newActiveBends;
    }
}

void Network::find_and_memorize_patterns_of_inputs()
{

}

void Network::memorize_minimal_repeated_pattern(Circuit inCircuit)
{
    if (inCircuit.is_first_consequence_placed_inside_one_higher_node()) {

    } else {
        create_higher_node_for(inCircuit);
    }
}

Node Network::create_higher_node_for(Circuit inCircuit) {
    Node higherNode(inCircuit);
    node.push_back(higherNode);

    return higherNode;
}



void Network::prepareOutputOnMotors() {

}


}


