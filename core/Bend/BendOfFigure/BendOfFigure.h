#pragma once

#include "core/Bend/Bend.h"

/// @image html position2.png


class BendOfFigure: public Bend
{
public:
    BendOfFigure();

private:
    // essential
    Node* nodeOfWholeFigure;
    vector<Bend*> freeBend;

};
