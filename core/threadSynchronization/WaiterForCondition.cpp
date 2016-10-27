#include "WaiterForCondition.h"

WaiterForTask::WaiterForTask()
{

}

void WaiterForTask::waitForTask()
{
    std::unique_lock<std::mutex> uniqueLock(mutex);
    //mutex.lock();
    while (!needToProceed) {
        condition.wait(uniqueLock);
    }
    needToProceed = false;
}

void WaiterForTask::prepareToNextTask()
{
    //std::unique_lock<std::mutex> uniqueLock(mutex);

    mutex.unlock();
}

void WaiterForTask::waitForTaskCompletion()
{
    //std::unique_lock<std::mutex> uniqueLock(mutex);
    mutex.lock();
}

void WaiterForTask::proceedWithTask()
{
    needToProceed = true;
    mutex.unlock();
    condition.notify_all();
}
