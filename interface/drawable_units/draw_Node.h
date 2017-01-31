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
    Node(const render::Node &other_node);
    void update_according_to_network();

    std::vector<Drawable_unit*> get_parts_inside_rect(Rect rect);
    Drawable_unit* get_part_under_point(Point point);
    void deselect_all_parts();

    int get_radius() const;
    QOpenGLTexture* get_texture() const;

    void draw()const;


std::vector<render::Hub> hubs;
private:
    friend Hub& Hub::add_next_hub();

    std::vector<core::Bend> find_unaccounted_real_bends();
    std::vector<core::Figure_bend> find_unaccounted_real_hubs() const;
    void add_bend_corresponding_to(core::Bend real_bend);

    void draw_links_to_bends() const;
    void draw_links_to_first_hubs() const;

    render::Hub& add_first_hub();
    Hub& add_next_hub(Hub& in_hub);

    std::vector<render::Bend> bends;
    std::vector<render::Hub*> first_hubs;

    //std::set<core::Bend>

    core::Node node;
};

}
