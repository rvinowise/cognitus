#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"


namespace core {
    class Bend;
}

namespace render {

class Node;

class Bend: public Drawable_unit
{
public:
    Bend();

    void draw() const;
    void draw_links_to_next_bends() const;
    Color get_links_to_next_bends_color() const;

    int get_radius()const;
    QOpenGLTexture* get_texture()const;

private:
    virtual const std::vector<core::Bend>& get_array_of_next_bends() const;
};


}
