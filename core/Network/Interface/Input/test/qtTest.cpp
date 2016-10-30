#include "core/test/alltests.h"


namespace test {


void Input::init_input_characteristics()
{
    core::network = new core::Network();
    qtyInputs = 50;
    qtyIterations = 10000;
    network->input.initNodes(qtyInputs);
}

void Input::bring_inputs_to_representation_of_network()
{
    //size_t qtyInputs = qrand()*10000;
    init_input_characteristics();
    concoct_input_history();
    input_history_in_cycle();
    check_network_validity();



}

void Input::concoct_input_history()
{
    for (size_t i_iter = 0; i_iter < qtyIterations; i_iter++) {
        QBitArray inputFromOutside(qtyInputs);
        for (size_t i_input = 0; i_input < qtyInputs; i_input++) {
            if (random(50) == 0) {
                inputFromOutside.setBit(i_input);
                break;
            }
        }
        inputHistory.append(inputFromOutside);
    }
}

std::atomic_size_t i_iteration;
void Input::input_history_in_cycle()
{
    i_iteration = -1;
    for (int i_iter = 0; i_iter < qtyIterations; i_iter++) {
        i_iteration++;
        debug_msg(QString("start input iteration %1").arg(i_iter).toLocal8Bit());
        network->input.beginSettingInputFromOutside();

        debug_msg(QString("inside iteration %1").arg(i_iter).toLocal8Bit());
        QBitArray inputFromOutside = inputHistory[i_iter];
        debug_msg("Mock::inputHistoryInCycle");
        for (size_t i_input=0; i_input < qtyInputs; i_input++) {
            if (inputFromOutside.testBit(i_input)) {
                network->input.prepareToFire(i_input);
            }
        }
        network->input.endSettingInputFromOutside(i_iteration, inputFromOutside.count(true));
    }
    network->input.wait_for_insertion_of_input();
}

void Input::check_network_validity()
{
    ActiveBends* lastAddedBends = network->getLastActiveBends();

    std::vector<Bend*>* bendsOfIteration = &lastAddedBends->bend;
    for (size_t i_iter = qtyIterations-1; i_iter > 0; i_iter--) {
        if (inputHistory[i_iter].count(true) > 0) {
            debug_msg(QString("start checking ineration %1").arg(i_iter).toLocal8Bit());
            check_if_all_bends_of_input_iteration_have_the_same_previous_bends(bendsOfIteration);
            debug_msg(QString("#2 start checking ineration %1").arg(i_iter).toLocal8Bit());
            compare_inputted_array_with_nodes_in_network(inputHistory[i_iter], bendsOfIteration);
            bendsOfIteration = get_bends_of_previous_input_iteration(bendsOfIteration);
        }
    }
}

void Input::check_if_all_bends_of_input_iteration_have_the_same_previous_bends
(std::vector<Bend*>* bendsOfIteration)
{
    QVERIFY(bendsOfIteration->size() > 0);

    size_t any_from_equal_ones = 0;
    std::vector<Bend*>* etalonPrevBends = &bendsOfIteration->at(any_from_equal_ones)->prevBend;
    size_t etalonQtyPrevBends = etalonPrevBends->size();

    size_t first_brother_bend_of_iteration = 1;
    for (size_t i_this_iteration_bend = first_brother_bend_of_iteration;
         i_this_iteration_bend < bendsOfIteration->size();
         i_this_iteration_bend++)
    {
        auto prevBendsOfBrothers = &bendsOfIteration->at(i_this_iteration_bend)->prevBend;
        QVERIFY(etalonPrevBends->size() == prevBendsOfBrothers->size());

        for (size_t i_prevBend = 0; i_prevBend < etalonQtyPrevBends; i_prevBend++) {
            QVERIFY2(etalonPrevBends->at(i_prevBend) == prevBendsOfBrothers->at(i_prevBend),
                     QString("i_prevBend=%1 i_this_iteration_bend=%2\n"
                             "etalonPrevBends[i_prevBend]=%3 prevBendsOfBrothers[i_prevBend]=%4").
                     arg(i_prevBend).arg(i_this_iteration_bend).
                     arg((size_t)&etalonPrevBends[i_prevBend]).arg((size_t)&prevBendsOfBrothers[i_prevBend]).toLocal8Bit());
        }
    }
}


void Input::compare_inputted_array_with_nodes_in_network
(QBitArray inputFromOutside, const std::vector<Bend*>* bendsOfInput)
{
    //for (Bend* bend : *bendsOfInput) {
    for (size_t i_bend=0; i_bend < bendsOfInput->size(); i_bend++) {
        Bend* bend = bendsOfInput->at(i_bend);
        InterfaceNode* node = static_cast<InterfaceNode*>(bend->node);
        size_t nodeIndex = node->get_index_in_interface_array();
        if (inputFromOutside.testBit(nodeIndex) == false) {
            bool errorFound = true;
        }
        QVERIFY(inputFromOutside.testBit(nodeIndex) == true);

        inputFromOutside.clearBit(nodeIndex);
    }
    //QVERIFY(inputFromOutside.isNull());
    for (size_t i_possible_neglected_input_signal = 0;
         i_possible_neglected_input_signal < inputFromOutside.size();
         i_possible_neglected_input_signal++) {

        QVERIFY(!inputFromOutside.testBit(i_possible_neglected_input_signal));
    }
}

std::vector<Bend*>* Input::get_bends_of_previous_input_iteration(const std::vector<Bend*>* bendsOfIteration)
{
    size_t anyFromEqualOnes = 0;
    return &bendsOfIteration->at(anyFromEqualOnes)->prevBend;
}



}


