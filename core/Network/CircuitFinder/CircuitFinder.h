#pragma once

#include <vector>

#include "core/Network/Circuit/Circuit.h"

namespace core {

class CircuitFinder
{
public:
    CircuitFinder();

    std::vector<Circuit> find_circuits_backward(const Bend& initialBend);
};


}
