#pragma once

#include <mutex>
#include <condition_variable>


namespace core {



class Waiter_for_task
{
public:
    Waiter_for_task();
    ~Waiter_for_task();

    void worker_wait_for_task();
    void worker_prepare_for_next_task();

    void master_wait_for_task_completion();
    void master_has_given_a_task();


private:
    std::mutex master_mutex;
    std::mutex worker_mutex;
    bool worker_needs_to_proceed;
    bool master_needs_to_proceed;
    std::condition_variable condition;

};

}
