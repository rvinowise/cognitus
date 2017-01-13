#pragma once

#include "core/Bend/Bend.h"

/// @image html C:/ydisk/program/cognitus/core/Bend/FreeBend/position1.png

namespace core {

class FreeBend: public Bend
{
public:
    FreeBend();

private:
    // essential
    std::vector<Bend*> bendOfFigure;
};

}
