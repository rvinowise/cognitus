#include "WaiterForCondition.h"
#include <qdebug.h>

/*std::mutex g_mutexExtra;
std::mutex g_mutexIntra;
bool needToProceed;
std::condition_variable condition;*/
namespace core {

WaiterForTask::WaiterForTask()
{
    //qDebug("WaiterForTask()");
}

WaiterForTask::~WaiterForTask()
{
    //qDebug("~WaiterForTask()");
}

void WaiterForTask::worker_wait_for_task(std::unique_lock<std::mutex>* uniqueLock)
{
    while (!needToProceed) {
        qDebug("waitForTask :: condition.wait(uniqueLock) (unlocks the mutexIntra)");
        condition.wait(*uniqueLock);
        qDebug("waitForTask :: I'm notifyed (OK-mutexIntra.lock)");
    }
}
void WaiterForTask::worker_prepare_for_next_task()
{
    needToProceed = false;
    //qDebug("prepareToNextTask :: mutexExtra.unlock");
    //mutex.unlock();
    //qDebug("prepareToNextTask :: OK-mutexExtra.unlock");
}


void WaiterForTask::master_wait_for_task_completion()
{
    qDebug("waitForTaskCompletion :: mutexExtra.lock");
    mutex.lock();
    qDebug("waitForTaskCompletion :: OK-mutexExtra.lock");
}
void WaiterForTask::master_gave_task()
{
    needToProceed = true;
    qDebug("proceedWithTask :: mutexExtra.unlock()");
    mutex.unlock();
    qDebug("proceedWithTask :: before notify");
    condition.notify_one();
    qDebug("proceedWithTask :: notifyed");
}

}
