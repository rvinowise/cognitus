#pragma once

#include "Interface/Input/Input.h"
#include "Interface/Output/Output.h"
#include "ActiveBend/ActiveBend.h"

#include <vector>
#include <thread>

class Network
{

public:
    Network();

    Input input;
    Output output;

    void step();



private:
    friend Input;
    friend Output;
    void constructCurrentStructureOfNodes();
    void prepareOutputOnMotors();
    void registerActivationOfExistingNodes();
    void extendNodesAndCreateNewOnes();

    void connectLastBendsToNewOnes();
    void saveNewActivatedBend(Bend* inBend);
    void createNewHighNodes();
    void saveLastFreeBend(Bend* inBend);


    ActiveBends lastActiveBends;
    ActiveBends newActiveBends;

    std::thread* threadProcessInput;
};


extern Network network;
