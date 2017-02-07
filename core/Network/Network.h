#pragma once

#include "Interface/Input/Input.h"
#include "Interface/Output/Output.h"
#include "ActiveBend/ActiveBend.h"
#include "CircuitFinder/CircuitFinder.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"

#include <vector>
#include <thread>


namespace core {

class iterator_node_BFS;

struct High_nodes
{
    iterator_node_BFS iter_begin;
    iterator_node_BFS begin();
    iterator_node_BFS end();
};

class Network
{

public:
    Network();
    ~Network();
    void deallocate_all_entities_of_network();

    Input input;
    Output output;

    CircuitFinder circuitFinder;

    void step();

    ActiveBends& getLastActiveBends();

    void prepare_to_new_input_iteration();
    void save_new_activated_bend(Bend inBend);

    iterator_node_BFS begin();
    iterator_node_BFS end();
    High_nodes high_nodes();
    typedef Node value_type;

private:
    friend class Input;
    friend class Output;
    void prepareOutputOnMotors();

    void prolongate_history_of_inputs();
    void find_and_memorize_patterns_of_inputs();
    void memorize_minimal_repeated_pattern(Circuit inCircuit);
    Node create_higher_node_for(Circuit inCircuit);

    ActiveBends* lastActiveBends;
    ActiveBends* newActiveBends;
    std::vector<Node> node;

    std::thread* threadProcessInput;
};

extern Network* global_network;

}
