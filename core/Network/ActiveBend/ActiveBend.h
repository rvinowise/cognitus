#pragma once

#include "../../Bend/Bend.h"

#include <vector>
using namespace std;


class ActiveBends
{
public:
    ActiveBends(){}

    void connectThisBendsToOthers(ActiveBends* nextActiveBend);

    vector<Bend*> bend;
};
