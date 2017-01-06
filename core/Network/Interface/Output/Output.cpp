#include "Output.h"

#include "core/Network/Network.h"

namespace core {

Output::Output()
{
    init_processing_thread();
}

void Output::begin_getting_output_from_outside()
{
    waiterForChangeOfOutput.master_wait_for_task_completion();
}

void Output::end_getting_output_from_outside()
{
    waiterForChangeOfOutput.master_gave_task();
}

bool Output::is_prepared_for_output(std::size_t index)
{
    return Interface::isPreparedToFire(index);
}

void Output::init_processing_thread()
{
    threadProcessOutput = new std::thread(
                &Output::produce_outputs_for_representation_of_client, this);
}



void Output::produce_outputs_for_representation_of_client()
{
    while (this) {
        waiterForChangeOfOutput.worker_wait_for_task();

        network->prepare_to_new_input_iteration();
        firePreparedNodes();
        network->prolongate_history_of_inputs();

        waiterForChangeOfOutput.worker_prepare_for_next_task();
    }
}



}
