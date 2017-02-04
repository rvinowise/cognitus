#pragma once

#include <vector>
#include <map>
#include <unordered_set>
#include "interface/drawable_units/Drawable_unit.h"

namespace core {
    class Hub;
    class Bend;
    class Node;
    class iterator_hub_BFS;
    //class iterator_BFS;
}

namespace render {

using namespace core;

class Node: public Drawable_unit
{
public:
    Node();
    Node(const Node& other);
    Node(Node&& other);
    operator=(const Node& other);

    std::vector<Drawable_unit> get_parts_inside_rect(Rect rect);
    Drawable_unit get_part_under_point(Point point);
    void deselect_all_parts();

    int get_radius()const;
    QOpenGLTexture* get_texture()const;

    void draw();

    virtual const std::vector<core::Bend>& bends() const;
    virtual const std::vector<core::Hub>& first_hubs() const;

    virtual core::iterator_hub_BFS begin();
    virtual core::iterator_hub_BFS end();
    typedef Hub value_type;
private:

    render::Bend& get_bend_in_margin();


    void draw_links_to_bends() const;
    void draw_links_to_first_hubs() const;

};

}
