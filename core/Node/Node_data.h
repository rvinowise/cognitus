#pragma once

#include <vector>

#include "core/Bend/Bend.h"


namespace core {

class Node_data
{
    friend class Node;
    Node_data();
private:
    std::vector<Bend> bend;
    Bend lower_chain_bend;
};





}
