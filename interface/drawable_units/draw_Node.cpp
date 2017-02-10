#include "draw_Node.h"

#include <algorithm>

#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "interface/RenderingWidget.h"
#include "interface/algorithms.h"
#include "core/test/Debug_inspector.h"

#include "core/test/randomFunc.h" //test

namespace render {

using std::vector;

Node::Node():
    Drawable_unit()
{
}

Node::Node(const Node &other):
    Drawable_unit(other)
{
}

Node::Node(Node &&other):
    Drawable_unit(std::move(other))
{
}



int Node::get_radius()const
{
    return 10;
}
QOpenGLTexture* Node::get_texture()const
{
    return renderingWidget->textures[0];
}




vector<Drawable_unit> Node::get_parts_inside_rect(Rect rect)
{
    vector<Drawable_unit> result;
    for (core::Bend bend: bends()) {
        if (bend.is_inside(rect)) {
            result.push_back(bend);
        }
    }
    for (core::Hub hub: *this) {
        if (hub.is_inside(rect)) {
            result.push_back(hub);
        }
    }
    return result;
}

Drawable_unit Node::get_part_under_point(Point point)
{
    if (has_inside(point)) {
        return *this;
    }
    for (core::Bend bend: bends()) {
        if (bend.has_inside(point)) {
            return bend;
        }
    }
    for (core::Hub hub: *this) {
        if (hub.has_inside(point)) {
            return hub;
        }
    }
    return Drawable_unit::get_empty();
}

void Node::deselect_all_parts()
{
    deselect();
    for (core::Bend bend: bends()) {
        bend.deselect();
    }
    for (core::Hub hub: *this) {
        hub.deselect();
    }
}

void Node::dispose_hubs_into_positions()
{
    std::for_each(begin(), end(),
                  [this](core::Hub hub){
        hub.position() = position() +
                Point(test::random(200), test::random(200));
    });
}


void Node::draw()
{
    std::for_each(bends().begin(), bends().end(), [](core::Bend bend){bend.draw();});
    std::for_each(this->begin(), this->end(), [](const core::Hub hub){hub.draw();});
    Drawable_unit::draw();

    //draw_links_to_first_hubs();
    //draw_links_to_bends();
}

void Node::draw_links_to_bends() const
{
    std::vector<Vertex_colored> vertices_of_links;
    Point attachment = this->position() + Point(0,-get_radius()+1);
    Color color_link = Color::fromRgbF(0,0,0,0.2);
    Color color_begin = (is_selected() ? /*color_link+*/selection_color : color_link);
    for (core::Bend bend: bends()) {
        vertices_of_links.push_back(Vertex_colored(attachment, color_begin));
        Color color_end = (bend.is_selected() ? /*color_link+*/selection_color : color_link);
        vertices_of_links.push_back(Vertex_colored(bend.position(), color_end));
    }

    draw_lines(vertices_of_links);

}

void Node::draw_links_to_first_hubs() const
{
    std::vector<Vertex_colored> vertices_of_links;
    Point attachment = this->position() + Point(0,get_radius()-1);
    Color color_link = Color::fromRgbF(0,0,0,0.5);
    Color color_begin = (is_selected() ? /*color_link+*/selection_color : color_link);
    for (core::Hub hub: first_hubs()) {
        vertices_of_links.push_back(Vertex_colored(attachment, color_begin));
        Point hub_attachment = hub.position() + Point(0,-hub.get_radius()+1);
        Color color_end = (hub.is_selected() ? /*color_link+*/selection_color : color_link);
        vertices_of_links.push_back(Vertex_colored(hub_attachment, color_end));
    }

    draw_lines(vertices_of_links);
}



}
