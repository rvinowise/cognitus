#pragma once

#include "core/Network/Node/Bend/Bend.h"

#include <vector>


namespace core {


class Synchro_bends
{
public:
    Synchro_bends(){}

    void connect_this_bends_to_others(Synchro_bends& next);

    std::vector<Bend>& get_bends();
    std::vector<Bend> bends;

    std::vector<Node> get_nodes();
};

}
