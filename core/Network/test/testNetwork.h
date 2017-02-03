#pragma once

#include "core/Network/Network.h"


namespace test {


class Network
{
public:
    Network(core::Network& in_network);

    void init_common_data_for_all_tests();

    void work_of_network();

    void construct_network_ignoring_interface();
    void deallocation_of_all_entities();

    core::Network& network;
};





}
