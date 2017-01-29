#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Bend.h"

namespace render {

class Bend: public Drawable_unit
{
public:
    Bend();
    void update_according_to_network(){};
    void draw();

    int get_radius();
    QOpenGLTexture* get_texture();
private:


    core::Bend bend;
};


}
