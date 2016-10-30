#pragma once

#include "core/Bend/Bend.h"

/// @image html position2.png

namespace core {

class BendOfFigure: public Bend
{
public:
    BendOfFigure();

private:
    // essential
    Node* nodeOfWholeFigure;
    std::vector<Bend*> freeBend;

};


}
