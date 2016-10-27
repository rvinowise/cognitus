#pragma once

#include "../Bend/Bend.h"

#include <vector>

using namespace std;

class Node
{
//friend class Bend;
public:
    void fire();

    bool isLowest();
    void expectLowerBends();

    friend Bend::Bend(Node* masterNode);
private:
    // essential
    vector<Bend* > bend;
    Bend* lowerChainBend;

    // volatile


    void transmitExpectationForward();
    void addNewBendAsActive();
    void createHighNodes();

    void addBend();
};
