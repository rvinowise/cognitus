#pragma once

#include <vector>
#include <map>
#include <unordered_set>
#include "interface/drawable_units/Drawable_unit.h"
#include "interface/drawable_units/draw_Bend.h"
#include "interface/drawable_units/draw_Hub.h"

namespace core {
    class Hub;
    class Bend;
}

namespace render {

class Node: public Drawable_unit
{
public:
    Node();
    Node(Node&& other);

    std::vector<Drawable_unit*> get_parts_inside_rect(Rect rect);
    Drawable_unit* get_part_under_point(Point point);
    void deselect_all_parts();

    int get_radius()const;
    QOpenGLTexture* get_texture()const;

    void draw()const;

    virtual std::vector<core::Bend>& bends();
    virtual std::vector<core::Hub>& first_hubs();

private:

    render::Bend& get_bend_in_margin();


    void draw_links_to_bends() const;
    void draw_links_to_first_hubs() const;

};

}
