#pragma once

#include "Interface/Input/Input.h"
#include "Interface/Output/Output.h"
#include "ActiveBend/ActiveBend.h"

#include <vector>
#include <thread>

#ifdef debug_mode
#include <atomic>
#endif

namespace core {

#ifdef debug_mode
    extern std::atomic_size_t input_iteration;
#endif

class Network
{

public:
    Network();

    Input input;
    Output output;

    void step();

    ActiveBends* getLastActiveBends();

    void prepare_to_new_input_iteration();
    void save_new_activated_bend(Bend* inBend);



private:
    friend Input;
    friend Output;
    void constructCurrentStructureOfNodes();
    void prepareOutputOnMotors();
    void registerActivationOfExistingNodes();
    void extendNodesAndCreateNewOnes();

    void connect_last_bends_to_new_ones();

    void createNewHighNodes();
    void saveLastFreeBend(Bend* inBend);


    ActiveBends* lastActiveBends;
    ActiveBends* newActiveBends;

    std::thread* threadProcessInput;
};


extern Network* network;

}