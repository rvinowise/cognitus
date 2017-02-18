#pragma once

#include <vector>
#include <map>

#include "core/Network/Circuit/Circuit.h"

namespace core {

class CircuitFinder
{
public:
    CircuitFinder();

    Circuit find_last_circuit_backward(const Bend& last_end_bend);

private:    
    
};


}
