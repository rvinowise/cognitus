#include "core/test/allTests.h"

#include "core/test/Debug_inspector.h"

namespace test {


Input::Input(core::Network& inNetwork):
    network{inNetwork}
{

}

void Input::bring_inputs_to_representation_of_network()
{
    init_input_characteristics();
    concoct_input_history();
    input_history_in_cycle();
    check_network_validity();
}

void Input::init_input_characteristics()
{
    network.input.initNodes(qtyInputs);
}


void Input::concoct_input_history()
{
    for (size_t i_iter = 0; i_iter < qtyIterations; i_iter++) {
        std::bitset<qtyInputs> inputIterationFromOutside;
        for (size_t i_input = 0; i_input < qtyInputs; i_input++) {
            //if (random(10) == 0) {
                inputIterationFromOutside.set(i_input);
            //}
        }
        inputHistory.push_back(inputIterationFromOutside);
    }
}

std::atomic_size_t i_iteration;
void Input::input_history_in_cycle()
{
    i_iteration = -1;
    for (std::size_t i_iter = 0; i_iter < qtyIterations; i_iter++) {
        i_iteration++;
        network.input.begin_setting_input_from_outside();
        debug.message(boost::format("master:: inside iteration %1%")%i_iter);

        std::bitset<qtyInputs> inputFromOutside = inputHistory[i_iter];
        for (size_t i_input=0; i_input < qtyInputs; i_input++) {
            if (inputFromOutside.test(i_input)) {
                network.input.prepare_wire_for_input(i_input);
            }
        }
        try {
            network.input.end_setting_input_from_outside();
        } catch (std::bad_alloc) {
            debug.error(boost::format("not enought memory to save input data #%1%")%i_iter);
        }
    }
    network.input.wait_for_insertion_of_previous_input();
}

void Input::check_network_validity()
{
    ActiveBends& lastAddedBends = network.getLastActiveBends();

    const std::vector<Bend>* bendsOfIteration = &lastAddedBends.bends;
    for (size_t i_iter = qtyIterations-1; i_iter > 0; i_iter--) {
        if (inputHistory[i_iter].count() > 0) {
            debug.profiler.start("check_network_validity iteration");
            debug.message(boost::format("master:: check iteration %1%")%i_iter);
            check_if_all_bends_of_input_iteration_have_the_same_previous_bends(*bendsOfIteration);
            compare_inputted_array_with_nodes_in_network(inputHistory[i_iter], *bendsOfIteration);
            bendsOfIteration = &get_bends_of_previous_input_iteration(*bendsOfIteration);
            debug.profiler.stop("check_network_validity iteration");
        }
    }
}

void Input::check_if_all_bends_of_input_iteration_have_the_same_previous_bends
(const std::vector<Bend>& bendsOfIteration)
{
    VERIFY(bendsOfIteration.size() > 0);

    const size_t any_from_equal_ones = 0;
    const auto etalonPrevBends =
            bendsOfIteration.at(any_from_equal_ones).get_array_of_prev_bends();
    size_t etalonQtyPrevBends = etalonPrevBends.size();

    const size_t first_brother_bend_of_iteration = 1;
    for (size_t i_this_iteration_bend = first_brother_bend_of_iteration;
         i_this_iteration_bend < bendsOfIteration.size();
         i_this_iteration_bend++)
    {
        auto prevBendsOfBrothers =
                bendsOfIteration.at(i_this_iteration_bend).get_array_of_prev_bends();
        VERIFY(etalonPrevBends.size() == prevBendsOfBrothers.size());

        for (size_t i_prevBend = 0; i_prevBend < etalonQtyPrevBends; i_prevBend++) {
            VERIFY2(etalonPrevBends[i_prevBend] == prevBendsOfBrothers[i_prevBend],
                     boost::str(boost::format("i_prevBend=%1% i_this_iteration_bend=%2%\n"
                             "etalonPrevBends[i_prevBend]=%3% prevBendsOfBrothers[i_prevBend]=%4%")
                     % i_prevBend % i_this_iteration_bend
                     % (size_t)&etalonPrevBends[i_prevBend] % (size_t)&prevBendsOfBrothers[i_prevBend]).c_str());
        }
    }
}


void Input::compare_inputted_array_with_nodes_in_network
(std::bitset<qtyInputs> inputFromOutside, const std::vector<Bend>& bendsOfInput)
{
    for (auto bend: bendsOfInput) {
        auto node = static_cast<InterfaceNode&>(bend.get_master_node());
        size_t nodeIndex = node.get_index_in_interface_array();
        VERIFY(inputFromOutside.test(nodeIndex) == true);

        inputFromOutside.reset(nodeIndex);
    }
    for (size_t i_possible_neglected_input_signal = 0;
         i_possible_neglected_input_signal < (size_t)inputFromOutside.size();
         i_possible_neglected_input_signal++) {

        VERIFY(!inputFromOutside.test(i_possible_neglected_input_signal));
    }
}

const std::vector<Bend>& Input::get_bends_of_previous_input_iteration(const std::vector<Bend>& bendsOfIteration)
{
    size_t anyFromEqualOnes = 0;
    return bendsOfIteration[anyFromEqualOnes].get_array_of_prev_bends();
}



}


