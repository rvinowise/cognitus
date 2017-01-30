#include "Input.h"

#include "core/Network/Network.h"

namespace core {

Input::Input(Network &inNetwork):
    Interface(inNetwork)
{
    init_processing_thread();

}


void Input::init_processing_thread()
{
    threadProcessInput = new std::thread(
                &Input::bring_inputs_to_representation_of_network, this);
}

void Input::begin_setting_input_from_outside()
{
   wait_for_insertion_of_previous_input();
}

void Input::prepare_wire_for_input(std::size_t index)
{
    Interface::prepareToFire(index);
}


void Input::end_setting_input_from_outside()
{
    waiterForChangeOfInput.master_has_given_a_task();
}

void Input::wait_for_insertion_of_previous_input()
{
    waiterForChangeOfInput.master_wait_for_task_completion();
}

void Input::bring_inputs_to_representation_of_network()
{
    while (this) {
        waiterForChangeOfInput.worker_wait_for_task();

        network.prepare_to_new_input_iteration();
        firePreparedNodes();
        network.prolongate_history_of_inputs();

        waiterForChangeOfInput.worker_prepare_for_next_task();
    }
}

}
