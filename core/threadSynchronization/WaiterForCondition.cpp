#include "WaiterForCondition.h"
#include <qdebug.h>


namespace core {

Waiter_for_task::Waiter_for_task()
{
    worker_needs_to_proceed = false;
    master_needs_to_proceed = true;
}

Waiter_for_task::~Waiter_for_task()
{

}

void Waiter_for_task::worker_wait_for_task()
{
	std::unique_lock<std::mutex> uniqueLock(worker_mutex);
    while (!worker_needs_to_proceed) {
        try {
            condition.wait(uniqueLock);
        } catch (const std::exception& e) {
            //std::string errorInfo = e.what();
            //test::debug.error(boost::format(errorInfo));
        } catch (...) {
            //test::debug.error(boost::format("unknown"));
        }

    }
}
void Waiter_for_task::worker_prepare_for_next_task()
{
    
	master_mutex.lock();
    worker_needs_to_proceed = false;
    master_needs_to_proceed = true;
	master_mutex.unlock();

	condition.notify_one();
}


void Waiter_for_task::master_wait_for_task_completion()
{
	std::unique_lock<std::mutex> uniqueLock(master_mutex);
    while (!master_needs_to_proceed) {
		condition.wait(uniqueLock);
	}
	
}
void Waiter_for_task::master_has_given_a_task()
{
    worker_mutex.lock();
    worker_needs_to_proceed = true;
    master_needs_to_proceed = false;
    worker_mutex.unlock();

    condition.notify_one();
}

}
