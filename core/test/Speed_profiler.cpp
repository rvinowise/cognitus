#include "Speed_profiler.h"

#include <chrono>

#include "core/test/Debug_inspector.h"


namespace test {

Speed_profiler::Speed_profiler()
{

}

void Speed_profiler::startTimer(const char *action)
{
    if (startedActions.count(action) > 0) {
        throw std::exception();/*((boost::format(
            "Speed_profiler::startTimer(%1%) timer is already started")
            %action).str());*/
    }
    startedActions[action] = getTime();
}

void Speed_profiler::stopTimer(const char *action)
{
    //if (startedActions) {

    //}
    unsigned int startTime = startedActions[action];
    unsigned int endTime = getTime();
    unsigned int executionTime = endTime - startTime;

    if (completedActions.count(action)) {
        Action_data data = completedActions[action];
        data.executionTimes.push_back(executionTime);
        data.totalExecutionTime += executionTime;
        completedActions[action] = data;
    } else {
        completedActions[action] = Action_data(executionTime);
    }

    startedActions.erase(action);
}

void Speed_profiler::calulate_average_execution_time()
{
    for (auto action : completedActions) {
        Action_data& actionData = completedActions[action.first];
        actionData.averageExecutionTime =
            static_cast<unsigned int>(actionData.totalExecutionTime /
                                      actionData.executionTimes.size());
        //completedActions.push_back();
    }
}

void Speed_profiler::write_resume()
{
    calulate_average_execution_time();
    debug.message("speed resume");
    for (const auto action : completedActions) {
        auto actionData = action.second;
        debug.message((boost::format("%1% : total=%2% average=%3%")%
                       action.first% actionData.totalExecutionTime% actionData.averageExecutionTime));
    }
}

unsigned int Speed_profiler::getTime()
{
    return std::chrono::system_clock::now().time_since_epoch().count();
}

}
