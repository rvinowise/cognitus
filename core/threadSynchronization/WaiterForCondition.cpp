#include "WaiterForCondition.h"
#include <qdebug.h>

#ifdef debug_mode
#include "core/debugStuff.h"
#endif

namespace core {

WaiterForTask::WaiterForTask()
{

}

WaiterForTask::~WaiterForTask()
{

}

void WaiterForTask::worker_wait_for_task(std::unique_lock<std::mutex>* uniqueLock)
{
    while (!needToProceed) {
        try {
            condition.wait(*uniqueLock);
        } catch (const std::exception& e) {
            std::string errorInfo = e.what();
            error_msg(boost::format(errorInfo));
        } catch (...) {
            error_msg(boost::format("unknown"));
        }

    }
}
void WaiterForTask::worker_prepare_for_next_task()
{
    needToProceed = false;
    master_mutex.unlock();
}


void WaiterForTask::master_wait_for_task_completion()
{
    master_mutex.lock();
}
void WaiterForTask::master_gave_task()
{
    worker_mutex.lock();
    needToProceed = true;
    worker_mutex.unlock();

    condition.notify_one();
}

}
