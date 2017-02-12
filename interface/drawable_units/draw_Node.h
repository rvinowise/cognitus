#pragma once

#include <vector>
#include <map>
#include <unordered_set>
#include "interface/drawable_units/Drawable_unit.h"
#include "interface/View_data/View_data.h"

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

    std::vector<Drawable_unit> get_parts_inside_rect(Rect rect);
    Drawable_unit get_part_under_point(Point point);
    void deselect_all_parts();
    void dispose_hubs_into_positions();

    static const float radius;
    int get_radius()const;
    static QOpenGLTexture* get_texture();

    void prepare_draw_data(std::vector<Vertex_colored>& vertices)const;
    void prepare_links_to_bends(std::vector<Vertex_colored>& vertices) const;
    void prepare_links_to_first_hubs(std::vector<Vertex_colored>& vertices) const;

    typedef Hub value_type;


private:

    render::Bend& get_bend_in_margin();

    void draw_links_to_bends() const;
    void draw_links_to_first_hubs() const;


    virtual const std::vector<core::Bend>& bends() const = 0;
    virtual const std::vector<core::Hub>& first_hubs() const = 0;

    virtual core::iterator_hub_BFS begin() = 0;
    virtual core::iterator_hub_BFS end() = 0;
};

}
