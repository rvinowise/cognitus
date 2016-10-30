#pragma once

#include "core/Bend/Bend.h"

namespace core {

class LineOfCircuit
{
public:
    LineOfCircuit(){};
private:
    Bend* start;
    Bend* end;
};

class Circuit
{
public:
    Circuit();

    Bend* getFirstStartBend();
    Bend* getSecondStartBend();
    Bend* getFirstEndBend();
    Bend* getSecondEndBend();
private:
    LineOfCircuit firstLine;
    LineOfCircuit secondLine;
};

}
