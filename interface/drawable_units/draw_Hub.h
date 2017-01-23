#pragma once

#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Figure_bend/Figure_bend.h"

namespace render {

class Hub: public Drawable_unit
{
public:
    Hub();

private:
    core::Figure_bend hub;
};

}
