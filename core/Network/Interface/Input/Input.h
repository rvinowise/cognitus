#pragma once

#include "../Interface.h"

#include "core/threadSynchronization/WaiterForCondition.h"
#include <thread>

namespace core {


class Input: public Interface
{
public:
    Input(Network &inNetwork);

    void begin_setting_input_from_outside();
    void prepare_wire_for_input(std::size_t index);
    void end_setting_input_from_outside();

    void wait_for_insertion_of_previous_input();


private:
    void init_processing_thread();

    void bring_inputs_to_representation_of_network();

    Waiter_for_task waiterForChangeOfInput;
    std::thread*  threadProcessInput;


};


}
