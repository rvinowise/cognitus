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
    void draw() const;

    int get_radius() const;
    QOpenGLTexture* get_texture() const;

    bool operator ==(const core::Bend& real_bend) const;
private:


    core::Bend bend;
};


}
