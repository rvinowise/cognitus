#include "Speed_profiler.h"



#include "core/test/Debug_inspector.h"




namespace test {

Speed_profiler::Speed_profiler()
{

}

Speed_profiler::~Speed_profiler()
{
}

void Speed_profiler::start(const char *action)
{
    if (startedActions.count(action) > 0) {
        throw ((boost::format(
            "Speed_profiler::startTimer(%1%) timer is already started")
            %action).str());
    }
    startedActions[action] = get_time();
}

void Speed_profiler::stop(const char *action)
{

    time_point startTime = startedActions[action];
    time_point endTime = get_time();
    duration executionTime = endTime - startTime;

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
            static_cast<duration>(actionData.totalExecutionTime /
                                      actionData.executionTimes.size());
    }
}

void Speed_profiler::write_resume()
{
    using namespace std::chrono;
    calulate_average_execution_time();
    typedef std::chrono::duration<int, std::ratio<1,100>> time_unit_t;
    debug.message("SPEED RESUME (centi-seconds): ");
    for (const auto action : completedActions) {
        auto actionData = action.second;

        int total_time = duration_cast<time_unit_t>
                (actionData.totalExecutionTime).count();
        int average_time = duration_cast<time_unit_t>
                (actionData.averageExecutionTime).count();
        /*std::string total_time{
            actionData.totalExecutionTime.count()};
        std::string average_time{
            actionData.averageExecutionTime.count()};*/
        debug.message((boost::format("%1% : total %2% | average %3%")%
        action.first% total_time% average_time));
    }
}

time_point Speed_profiler::get_time()
{
    return std::chrono::high_resolution_clock::now();
}

}
