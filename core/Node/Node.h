#pragma once

#include "../Bend/Bend.h"

#include <vector>

namespace core {

class Node
{
public:
    virtual void fire();

    bool isLowest();
    void expectLowerBends();

    friend Bend::Bend(Node& masterNode);

    std::vector<Bend > bend;
private:

    Bend lowerChainBend;

    void add_new_bend_as_active();
    void createHighNodes();

    void addBend();    
};


}
