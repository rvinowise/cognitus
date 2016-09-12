#pragma once

#include "Interface/Input/Input.h"
#include "Interface/Output/Output.h"
#include "ActiveBend/ActiveBend.h"

#include <vector>

class Network
{
public:
    Network();

    Input input;
    Output output;

    void step();
    void fireInputAndThenHigherNodes();
    void connectLastBendsToNewOnes();
    void saveNewActivatedBend(Bend* inBend);
    void createNewHighNodes();

	
    saveLastFreeBend(Bend* inBend);
private:
    ActiveBend lastActiveBend;
    ActiveBend newActiveBend;
};


extern Network network;
