#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Network/Node/Hub/Hub.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"

namespace render {

class Node;

class Hub: public Drawable_unit
{
public:
    Hub(const core::Hub& real_hub, render::Node& node);

    void update_according_to_network();
    void draw() const;

    int get_radius()const;
    QOpenGLTexture* get_texture() const;
    Color get_links_to_next_hubs_color() const;
    render::Hub& get_last_next_hub();

    bool operator==(const core::Hub& real_hub)const;
//private:
    void draw_links_to_next_hubs() const;

    render::Hub& add_next_hub(const core::Hub &real_hub);
    std::vector<render::Hub*> next_hubs;
    std::vector<render::Bend> bends;

    core::Hub hub;
    render::Node& node;
};

}

