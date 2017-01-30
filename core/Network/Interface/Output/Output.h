#pragma once

#include "../Interface.h"

#include "core/threadSynchronization/WaiterForCondition.h"
#include <thread>


namespace core {

class Output: public Interface
{
public:
    Output(Network &inNetwork);

    void begin_getting_output_from_outside();
    bool is_prepared_for_output(std::size_t index);
    void end_getting_output_from_outside();


private:
    void prepare_wire_for_output(std::size_t index);

    void init_processing_thread();

    void produce_outputs_for_representation_of_client();

    Waiter_for_task waiterForChangeOfOutput;
    std::thread*  threadProcessOutput;
};

}
