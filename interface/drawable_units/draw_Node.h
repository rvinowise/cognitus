#pragma once

#include "interface/drawable_units/Drawable_unit.h"
#include "core/Node/Node.h"

namespace render {

class Node: public Drawable_unit
{
public:
    Node();
private:
    core::Node node;
};

}
