#pragma once

#include <vector>

#include "Core/Bend/Bend.h"


namespace core {

class Node_data
{
    friend class Node;
private:
    std::vector<Bend> bend;
    Bend lowerChainBend;
};



}
