#pragma once

#include <boost/format.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

namespace test {


using duration = std::chrono::high_resolution_clock::duration;
using time_point = std::chrono::high_resolution_clock::time_point;

struct Action_data
{

    Action_data():
    totalExecutionTime{0},
    averageExecutionTime{0}
    {
    }
    Action_data(duration inTime):
    averageExecutionTime{0}
    {
        executionTimes.push_back(inTime);
        totalExecutionTime=inTime;
    }
    std::vector<duration> executionTimes;
    std::chrono::high_resolution_clock::duration totalExecutionTime;
    std::chrono::high_resolution_clock::duration averageExecutionTime;
};

class Speed_profiler
{
public:
    Speed_profiler();
    ~Speed_profiler();

    void start(const char* action = nullptr);
    void stop(const char* action = nullptr);

    void calulate_average_execution_time();
    void write_resume();
private:
    time_point get_time();
    std::unordered_map<const char*, time_point> startedActions;
    std::unordered_map<const char*, Action_data> completedActions;
};

}
