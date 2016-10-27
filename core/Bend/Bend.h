#pragma once


#include <vector>
#include <set>

using namespace std;

class Node;

class Bend
{
public:
    Bend(Node* masterNode);



    bool isExpectedByAll();

    void fire();
    bool isThisLastBendInChain();
    void transmitExpectationHorisontal();

    void expectedBy(Bend* expectingBend);
    void connectTo(Bend* toBend);


private:
    // essential
    vector<Bend*> prevBend;
    vector<Bend*> nextBend;

    Node* node;

    // volatile
    set<Bend*> firedBend;

};

