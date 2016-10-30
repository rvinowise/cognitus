#include "Input.h"

#include "core/Network/Network.h"
#include <QtCore>
#include <QtTest/QtTest>

namespace core {

Input::Input()
{
    inputSignalsAreExpected = true;
    initProcessingThread();

}


void Input::initProcessingThread()
{
    threadProcessInput = new std::thread(
                &Input::bringInputsToRepresentationOfNetwork, this);
}

void Input::beginSettingInputFromOutside()
{
    waiterForChangeOfInput.master_wait_for_task_completion();
}

#ifdef debug_mode
void Input::endSettingInputFromOutside(std::size_t iter, std::size_t qtySignals)
{
    this->iter = iter;
    this->qtySignals = qtySignals;
    waiterForChangeOfInput.master_gave_task();
}
#else
void Input::endSettingInputFromOutside()
{
    waiterForChangeOfInput.master_gave_task();
}
#endif

void Input::wait_for_insertion_of_input()
{
    waiterForChangeOfInput.master_wait_for_task_completion();
}

void Input::bringInputsToRepresentationOfNetwork()
{
    while (inputSignalsAreExpected) {
        std::unique_lock<std::mutex> uniqueLock(waiterForChangeOfInput.mutex);
        /*while (!waiterForChangeOfInput.needToProceed) {
            qDebug("waitForTask :: condition.wait(uniqueLock) (unlocks the mutexIntra)");
            waiterForChangeOfInput.condition.wait(uniqueLock);
            debug_msg(QString("waitForTask :: I'm notifyed iter:%1 qtySign:%2").
                      arg(iter).arg(qtySignals));
        }*/
        waiterForChangeOfInput.worker_wait_for_task(&uniqueLock);

        debug_msg(QString("Input::bringInputsToRepresentationOfNetwork iter:%1 qtySign:%2").
                  arg(iter).arg(qtySignals));
        network->prepare_to_new_input_iteration();
        firePreparedNodes();
        network->connect_last_bends_to_new_ones();

        waiterForChangeOfInput.worker_prepare_for_next_task();
    }
}

}
