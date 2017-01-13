#pragma once

#include <vector>

#include "core/Bend/Bend.h"


namespace core {

class Node_data
{
    friend class Node;
    Node_data();

    void connect_a_handle();
    void disconnect_a_handle();
private:
    std::vector<Bend> bend;
    Bend lower_chain_bend;
    std::size_t handles_qty;
};





}
