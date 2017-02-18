#include "Network.h"

#include <QtDebug>
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"


namespace core {


Moment Network::moment{Moment(0)};

Network::Network():
    input(*this), output(*this)
{
    last_active_bends = new Synchro_bends();
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

Synchro_bends& Network::get_last_active_bends()
{
    return *last_active_bends;
}



void Network::prepare_to_new_input_iteration()
{
    new_active_bends = new Synchro_bends();
}

void Network::save_new_activated_bend(Bend inBend)
{
    new_active_bends->bends.push_back(inBend);
}


iterator_node_BFS Network::begin()
{
    return iterator_node_BFS(*this);
}
iterator_node_BFS Network::end()
{
    return iterator_node_BFS();
}

High_nodes Network::high_nodes()
{
    High_nodes high_hodes;
    iterator_node_BFS iterator;
    iterator.go_to_high_nodes(*this);
    high_hodes.iter_begin = iterator;
    return high_hodes;
}

Moment Network::this_moment()
{
    return moment;
}

iterator_node_BFS High_nodes::begin()
{
    return iter_begin;
}
iterator_node_BFS High_nodes::end()
{
    return iterator_node_BFS();
}


void Network::process_inputted_data()
{
    prolongate_history_of_inputs();
    
    Bend new_bend = get_last_active_bends().bends.front();
    Circuit new_circuit = circuit_finder.find_last_circuit_backward(new_bend);
    if (new_circuit.is_complete()) {
        Node high_node = Node(new_circuit);
    }
    
    ++moment;
}

void Network::prolongate_history_of_inputs() {
    // incapsulate?
    if (!new_active_bends->bends.empty()) {
        last_active_bends->connect_this_bends_to_others(*new_active_bends);
        delete last_active_bends;
        last_active_bends = new_active_bends;
    } else {
        delete new_active_bends;
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

void Network::fire_node(Node& in_node)
{
    Bend new_bend = in_node.fire();
    save_new_activated_bend(new_bend);
}



void Network::prepareOutputOnMotors() {
    
}






}
