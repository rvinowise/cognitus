#pragma once

#include "core/Bend/Bend.h"

namespace core {

struct LineOfCircuit
{
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

    void putFirstStartBend(Bend&);
    void putSecondStartBend(Bend&);
    void putFirstEndBend(Bend&);
    void putSecondEndBend(Bend &);
private:
    LineOfCircuit firstLine;
    LineOfCircuit secondLine;
};

}
