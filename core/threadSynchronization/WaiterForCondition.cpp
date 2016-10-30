#include "WaiterForCondition.h"
#include <qdebug.h>

/*std::mutex g_mutexExtra;
std::mutex g_mutexIntra;
bool needToProceed;
std::condition_variable condition;*/

#ifdef debug_mode
#include "core/debugStuff.h"
#endif

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
        debug_msg(QString("waitForTask :: I'm notifyed iter:%1 qtySign:%2").
                  arg(iter).arg(qtySignals));
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
