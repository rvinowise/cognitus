#include "Input.h"

#include "core/Network/Network.h"

Input::Input()
{
    inputSignalsAreExpected = true;
    initProcessingThread();

}


void Input::initProcessingThread()
{
    threadProcessInput = new std::thread(
                &Input::bringInputsToRepresentationOfNetwork, this);
}

void Input::beginSettingInputFromOutside()
{
    waiterForChangeOfInput.waitForTaskCompletion();
}

void Input::prepareToFire(int index)
{
    node[index]->prepareToFire();
}

void Input::endSettingInputFromOutside()
{
    waiterForChangeOfInput.proceedWithTask();
}

void Input::bringInputsToRepresentationOfNetwork()
{
    while (inputSignalsAreExpected) {
        waiterForChangeOfInput.waitForTask();
        firePreparedNodes();
        network.connectLastBendsToNewOnes();
        waiterForChangeOfInput.prepareToNextTask();
    }
}

