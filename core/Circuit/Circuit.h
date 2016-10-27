#pragma once

#include "core/Bend/Bend.h"

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

