#include "WaiterForCondition.h"
#include <qdebug.h>

#ifdef debug_mode
#include "core/test/debugStuff.h"
#endif

namespace core {

WaiterForTask::WaiterForTask()
{
	needToProceed = false;
	master_need_to_proceed = true;
}

WaiterForTask::~WaiterForTask()
{

}

void WaiterForTask::worker_wait_for_task()
{
	std::unique_lock<std::mutex> uniqueLock(worker_mutex);
	while (!needToProceed) {
        try {
            condition.wait(uniqueLock);
        } catch (const std::exception& e) {
            std::string errorInfo = e.what();
            test::debug.error(boost::format(errorInfo));
        } catch (...) {
            test::debug.error(boost::format("unknown"));
        }

    }
}
void WaiterForTask::worker_prepare_for_next_task()
{
    
	master_mutex.lock();
	needToProceed = false;
	master_need_to_proceed = true;
	master_mutex.unlock();

	condition.notify_one();
}


void WaiterForTask::master_wait_for_task_completion()
{
	std::unique_lock<std::mutex> uniqueLock(master_mutex);
	while (!master_need_to_proceed) {
		condition.wait(uniqueLock);
	}
	
}
void WaiterForTask::master_gave_task()
{
    worker_mutex.lock();
    needToProceed = true;
	master_need_to_proceed = false;
    worker_mutex.unlock();

    condition.notify_one();
}

}
