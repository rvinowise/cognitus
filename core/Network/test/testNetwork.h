#pragma once

#include "core/Network/Network.h"


namespace test {


class Network
{
public:
    void init_data_for_tests();

    void work_of_network();

    void construct_network_ignoring_interface();
    void deallocation_of_all_entities();

    core::Network network;
};





}
