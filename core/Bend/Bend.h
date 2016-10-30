#pragma once


#include <vector>
#include <set>

namespace core {

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

    // essential
    std::vector<Bend*> prevBend;
    std::vector<Bend*> nextBend;
    Node* node;
private:

    // volatile
    std::set<Bend*> firedBend;

#ifdef debug_mode
    std::size_t indexInput;
#endif
};


}
