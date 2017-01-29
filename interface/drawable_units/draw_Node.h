#pragma once

#include <vector>
#include "interface/drawable_units/Drawable_unit.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"
#include "core/Node/Node.h"

namespace render {


class Node: public Drawable_unit
{
public:
    Node(core::Node real_node);
    void update_according_to_network();
    std::vector<Drawable_unit*> get_parts_inside_rect(Rect rect);
    Drawable_unit* get_part_under_point(Point point);
    void deselect_all_parts();

    int get_radius();
    QOpenGLTexture* get_texture();

    void draw();
private:
    std::vector<render::Bend> bends;
    std::vector<render::Hub> hubs;

    core::Node node;
};

}
