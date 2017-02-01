#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Bend.h"

namespace render {

class Node;

class Bend: public Drawable_unit
{
public:
    Bend(core::Bend real_bend, render::Node& node);
    void update_according_to_network(){};
    render::Bend* add_next_bend();

    void draw() const;
    void draw_links_to_next_bends() const;
    Color get_links_to_next_bends_color() const;

    static int get_radius();
    static QOpenGLTexture* get_texture();

    bool operator ==(const core::Bend& real_bend) const;
private:

    std::vector<render::Bend*> next_bends;
    core::Bend bend;
    render::Node& node;
};


}
