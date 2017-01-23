#pragma once

#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Bend.h"

namespace render {

class Bend: public Drawable_unit
{
public:
    Bend();

private:
    core::Bend bend;
};


}
