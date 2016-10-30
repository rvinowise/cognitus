#pragma once

#include "../../Bend/Bend.h"

#include <vector>


namespace core {


class ActiveBends
{
public:
    ActiveBends(){}

    void connectThisBendsToOthers(ActiveBends* nextActiveBend);

    std::vector<Bend*> bend;
};

}
