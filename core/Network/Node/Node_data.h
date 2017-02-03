#pragma once

#include <vector>

#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/auxiliary/Acquiring_handles/Acquiring_handles.h"

namespace core {

class Node_data: public Acquiring_handles
{
public:
    Node_data();

    size_t level;
    std::vector<Bend> bends;
    std::vector<Hub> hubs;
};





}
