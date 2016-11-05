#include "Input.h"

#include "core/Network/Network.h"
#include <QtCore>
#include <QtTest/QtTest>

namespace core {

Input::Input()
{
    initProcessingThread();

}


void Input::initProcessingThread()
{
    threadProcessInput = new std::thread(
                &Input::bring_inputs_to_representation_of_network, this);
}

void Input::begin_setting_input_from_outside()
{
    waiterForChangeOfInput.master_wait_for_task_completion();
}

void Input::prepare_wire_for_input(std::size_t index)
{
    Interface::prepareToFire(index);
}


void Input::end_setting_input_from_outside()
{
    waiterForChangeOfInput.master_gave_task();
}

void Input::wait_for_insertion_of_input()
{
    waiterForChangeOfInput.master_wait_for_task_completion();
}

void Input::bring_inputs_to_representation_of_network()
{
    while (this) {
        waiterForChangeOfInput.worker_wait_for_task();

        network->prepare_to_new_input_iteration();
        firePreparedNodes();
        network->connect_last_bends_to_new_ones();

        waiterForChangeOfInput.worker_prepare_for_next_task();
    }
}

}
