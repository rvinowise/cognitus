#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"

namespace render {


class Hub: public Drawable_unit
{
public:
    Hub();

    void update_according_to_network();
    void draw();

    int get_radius();
    QOpenGLTexture* get_texture();
private:
    std::vector<render::Hub> next_hubs;
    std::vector<render::Bend> bends;

    core::Figure_bend hub;
};

}

