#pragma once

#include <vector>

#include "core/Circuit/Circuit.h"

namespace core {

class CircuitFinder
{
public:
    CircuitFinder();

    std::vector<Circuit> find_circuits(const Bend& initialBend);
};


}
