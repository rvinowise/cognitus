#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"

namespace render {

class Node;

class Hub: public Drawable_unit
{
public:
    Hub();
    Hub(render::Node& node);
    Hub(const render::Hub &other_hub);

    void update_according_to_network();
    void draw() const;

    int get_radius() const;
    QOpenGLTexture* get_texture() const;
    Color get_links_to_next_hubs_color() const;
    render::Hub& get_last_next_hub();
//private:
    void draw_links_to_next_hubs() const;

    render::Hub& add_next_hub();
    std::vector<render::Hub*> next_hubs;
    std::vector<render::Bend> bends;

    core::Figure_bend hub;
    render::Node& node;
};

}

