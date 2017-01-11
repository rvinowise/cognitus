#pragma once

#include <mutex>
#include <condition_variable>

/*extern std::mutex g_mutexExtra;
extern std::mutex g_mutexIntra;
extern bool needToProceed;
extern std::condition_variable condition;*/

namespace core {



class WaiterForTask
{
public:
    WaiterForTask();
    ~WaiterForTask();

    void worker_wait_for_task();
    void worker_prepare_for_next_task();

    void master_wait_for_task_completion();
    void master_has_given_a_task();

    std::mutex master_mutex;
    std::mutex worker_mutex;
    bool worker_needs_to_proceed;
    bool master_needs_to_proceed;
    std::condition_variable condition;
private:

};

}
