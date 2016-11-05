#pragma once

#include <vector>
#include <bitset>

namespace test {


class testCircuitFinder
{
public:
    void find_some_circuits_in_network();

private:
    void init_test_characteristics();
    void concoct_input_signals();
    void check_if_circuits_are_found();

    static const size_t qtyInputs = 500;
    size_t qtyIterations;

    std::vector<std::bitset<qtyInputs>> inputHistory;
};

}
