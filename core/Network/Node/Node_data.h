#pragma once

#include <vector>

#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Hub/Hub.h"

namespace core {

class Node_data
{
public:
    Node_data();

    size_t level;
    std::vector<Bend> bends;
    std::vector<Hub> hubs;
};





}
