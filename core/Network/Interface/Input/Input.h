#pragma once

#include "../Interface.h"

#include "core/threadSynchronization/WaiterForCondition.h"
#include <thread>

namespace core {


class Input: public Interface
{
public:
    Input();

    void beginSettingInputFromOutside();
#ifdef debug_mode
    void endSettingInputFromOutside(std::size_t iter, std::size_t qtySignals);
    std::size_t iter;
    std::size_t qtySignals;
#else
    void endSettingInputFromOutside();
#endif
    void wait_for_insertion_of_input();


private:
    void initProcessingThread();

    void bring_inputs_to_representation_of_network();
    void waitForNewInputs();

    bool inputSignalsAreExpected;
    WaiterForTask waiterForChangeOfInput;
    std::thread*  threadProcessInput;

};


}
