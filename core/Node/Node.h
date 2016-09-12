#pragma once

#include "../Bend/Bend.h"

#include <vector>

using namespace std;

class Node
{
public:
    void fire();

    bool isLowest();
    void expectLowerBends();

private:
    // essential
    vector<Bend*> bend;
    Bend* freeBend;
    Bend* lowerChainBend;

    // volatile


    void transmitExpectationForward();
    void addNewActiveBend();
    void createHighNodes();

    void addBend();
};
