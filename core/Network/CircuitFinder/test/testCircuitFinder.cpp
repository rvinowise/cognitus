#include "testCircuitFinder.h"

#include "core/Network/Interface/Input/test/testInput.h"
#include "core/Circuit/Circuit.h"
#include "core/Network/CircuitFinder/CircuitFinder.h"
#include "core/test/randomFunc.h"

using namespace core;

namespace test {

void testCircuitFinder::find_some_circuits_in_network()
{
    //test::Input inputTester();
    //inputTester.concoct_input_history();


}

void testCircuitFinder::init_test_characteristics()
{
    /*core::network = new core::Network();
    qtyInputs = 100;
    qtyIterations = 1000;
    network->input.initNodes(qtyInputs);*/

    core::CircuitFinder circuitFinder;
    //circuitFinder.find_circuits();
}

void testCircuitFinder::concoct_input_signals()
{
    std::vector<core::Circuit> circuits;
    std::vector<int> firedInputs;
    for (size_t i_iter = 0; i_iter < qtyIterations; i_iter++) {
        std::bitset<qtyInputs> inputIterationFromOutside;
        for (size_t i_input = 0; i_input < qtyInputs; i_input++) {
            if (random(10) == 0) {
                inputIterationFromOutside.set(i_input);
                /*if (firedInputs.(i_input) != -1) {
                    core::Circuit newCircuit;
                    //newCircuit.putFirstStartBend();
                    circuits.push_back(Circuit());
                }*/
                firedInputs.push_back(i_input);
            }
        }
        inputHistory.push_back(inputIterationFromOutside);
    }
}



void testCircuitFinder::check_if_circuits_are_found()
{
    //core::network->circuitFinder.find_circuits()
}

}
