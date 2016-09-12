#pragma once

#include "../../Bend/Bend.h"

#include <vector>
using namespace std;


class ActiveBend
{
public:
    ActiveBend(){}

    void connectThisBendsToOthers(ActiveBend* nextActiveBend);

    vector<Bend*> bend;
};
