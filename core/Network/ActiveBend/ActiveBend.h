#pragma once

#include "core/Network/Node/Bend/Bend.h"

#include <vector>


namespace core {


class ActiveBends
{
public:
    ActiveBends(){}

    void connect_this_bends_to_others(ActiveBends& nextActiveBend);

    std::vector<Bend> bend;
};

}
