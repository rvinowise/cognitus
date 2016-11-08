#pragma once

#include <boost/format.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace test {

struct Action_data
{
    Action_data(){
        totalExecutionTime=0;
        averageExecutionTime = 0;
    }
    Action_data(unsigned int inTime) {
        executionTimes.push_back(inTime);
        totalExecutionTime=inTime;
        averageExecutionTime = 0;
    }
    std::vector<unsigned int> executionTimes;
    unsigned int totalExecutionTime;
    unsigned int averageExecutionTime;
};

class Speed_profiler
{
public:
    Speed_profiler();

    //void startTimer();
    void startTimer(const char* action = nullptr);

    //void stopTimer();
    void stopTimer(const char* action = nullptr);

    void calulate_average_execution_time();
    void write_resume();
private:
    unsigned int getTime();
    std::unordered_map<const char*, unsigned int> startedActions;
    std::unordered_map<const char*, Action_data> completedActions;
};

}
