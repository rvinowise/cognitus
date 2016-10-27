#pragma once

#include <mutex>
#include <condition_variable>

class WaiterForTask
{
public:
    WaiterForTask();

    void waitForTask();
    void prepareToNextTask();

    void waitForTaskCompletion();
    void proceedWithTask();


private:
    std::mutex mutex;
    bool needToProceed;
    std::condition_variable condition;

};

