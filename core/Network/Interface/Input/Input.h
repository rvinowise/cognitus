#pragma once

#include "../Interface.h"

#include "core/threadSynchronization/WaiterForCondition.h"
#include <thread>

class Input: public Interface
{
public:
    Input();

    void beginSettingInputFromOutside();
    void prepareToFire(int index);
    void endSettingInputFromOutside();


private:
    void initProcessingThread();

    void bringInputsToRepresentationOfNetwork();
    void waitForNewInputs();

    bool inputSignalsAreExpected;
    WaiterForTask waiterForChangeOfInput;
    std::thread*  threadProcessInput;

};

