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
    Hub(const core::Figure_bend& real_hub, render::Node& node);

    void update_according_to_network();
    void draw() const;

    static int get_radius();
    static QOpenGLTexture* get_texture();
    Color get_links_to_next_hubs_color() const;
    render::Hub& get_last_next_hub();

    bool operator==(const core::Figure_bend& real_hub)const;
//private:
    void draw_links_to_next_hubs() const;

    render::Hub& add_next_hub(const core::Figure_bend &real_hub);
    std::vector<render::Hub*> next_hubs;
    std::vector<render::Bend> bends;

    core::Figure_bend hub;
    render::Node& node;
};

}

