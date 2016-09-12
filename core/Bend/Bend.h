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

    void transmitExpectationForward();
    bool isThisLastBendInChain();
    void transmitExpectationHorisontal();

    void expectedBy(Bend* expectingBend);
    void connectTo(Bend* toBend);


private:
    vector<Bend*> prevBend;
    set<Bend*> firedBend;

    vector<Bend*> nextBend;
    Node* node;
    Node* highNode;


};

