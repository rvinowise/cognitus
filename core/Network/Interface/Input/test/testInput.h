#pragma once
#include "core/Network/Network.h"
#include <atomic>
#include <bitset>


namespace test {

using namespace core;


extern std::atomic_size_t i_iteration;

class Input
{
public:
    void bring_inputs_to_representation_of_network();

    void concoct_input_history();
    void input_history_in_cycle();

private:
    static const size_t qtyInputs = 100;
    static const size_t qtyIterations = 100;

    void init_input_characteristics();
    void check_network_validity();
    void check_if_all_bends_of_input_iteration_have_the_same_previous_bends(const std::vector<Bend>& bendsOfIteration);
    void compare_inputted_array_with_nodes_in_network(std::bitset<qtyInputs> inputIteration, const std::vector<Bend>& bendsOfIteration);
    std::vector<Bend>* get_bends_of_previous_input_iteration(const std::vector<Bend>& bendsOfIteration);



    std::vector<std::bitset<qtyInputs> > inputHistory;
};


}
