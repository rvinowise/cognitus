#pragma once

#include <vector>
#include <map>
#include <unordered_set>
#include "interface/drawable_units/Drawable_unit.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"
#include "core/Network/Node/Node.h"

namespace render {


class Node: public Drawable_unit
{
public:
    Node(core::Node real_node);
    void update_according_to_network();

    std::vector<Drawable_unit*> get_parts_inside_rect(Rect rect);//
    Drawable_unit* get_part_under_point(Point point);//
    void deselect_all_parts();//

    int get_radius()const;//
    QOpenGLTexture* get_texture()const;//

    void draw()const;//

    bool operator==(const core::Node& real_node)const;

private:
    friend Hub& Hub::add_next_hub(const core::Hub& real_hub);

    std::vector<core::Bend> find_unaccounted_real_bends();
    std::vector<core::Hub> find_unaccounted_real_hubs();
    void add_bend_corresponding_to(core::Bend real_bend);
    render::Bend& get_bend_in_margin();//
    void add_hub_corresponding_to(core::Hub real_hub);

    void draw_links_to_bends() const; //
    void draw_links_to_first_hubs() const;//

    render::Hub& add_first_hub(const core::Hub &real_hub);
    Hub& add_next_hub(Hub& in_hub);

    std::list<render::Bend> bends;
    std::list<render::Hub> hubs;
    std::vector<render::Hub*> first_hubs;

    core::Node node;
};

}
