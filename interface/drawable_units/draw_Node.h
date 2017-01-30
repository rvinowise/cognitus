#pragma once

#include <vector>
#include <map>
#include <unordered_set>
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
    vector<core::Bend> find_unaccounted_real_bends();
    vector<core::Figure_bend> find_unaccounted_real_hubs();
    void add_bend_corresponding_to(real_bend);


    std::vector<Drawable_unit*> get_parts_inside_rect(Rect rect);
    Drawable_unit* get_part_under_point(Point point);
    void deselect_all_parts();

    int get_radius();
    QOpenGLTexture* get_texture();

    void draw();
    void draw_links_to_bends();
    void draw_links_to_first_hubs();
private:
    std::vector<render::Bend> bends;
    std::vector<render::Hub> hubs;
    std::set<core::Bend>

    core::Node node;
};

}
