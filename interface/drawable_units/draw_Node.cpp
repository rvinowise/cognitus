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

render::Node Node::operator=(const Node &other)
{
    data = other.data;
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
    if (is_inside(rect)) {
        result.push_back(*this);
    }
    for (Bend bend: bends()) {
        if (bend.is_inside(rect)) {
            result.push_back(bend);
        }
    }
    for (Hub hub: *this) {
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
    for (Bend bend: bends()) {
        if (bend.has_inside(point)) {
            return bend;
        }
    }
    for (Hub hub: *this) {
        if (hub.has_inside(point)) {
            return hub;
        }
    }
    return Drawable_unit::get_empty();
}

void Node::deselect_all_parts()
{
    deselect();
    for (Bend bend: bends()) {
        bend.deselect();
    }
    for (Hub hub: *this) {
        hub.deselect();
    }
}

void Node::draw()
{
    std::for_each(bends().begin(), bends().end(), [](core::Bend bend){bend.draw();});
    std::for_each(this->begin(), this->end(), [](const core::Hub hub){hub.draw();});
    Drawable_unit::draw();

    draw_links_to_first_hubs();
    draw_links_to_bends();
}

const std::vector<core::Bend> &Node::bends() const
{
    throw_msg("render::Node::bends must call the function of core::Node");
}

const std::vector<core::Hub> &Node::first_hubs() const
{
    throw_msg("render::first_hubs::ends must call the function of core::Node");
}

iterator_hub_BFS Node::begin()
{
    throw_msg("render::Node::begin must call the function of core::Node");
}

iterator_hub_BFS Node::end()
{
    throw_msg("render::Node::end must call the function of core::Node");
}

void Node::dispose_hubs_into_positions()
{
    std::for_each(begin(), end(),
                  [this](core::Hub hub){
        hub.position() = position() +
                Point(test::random(200), test::random(200));
    });
}



void Node::draw_links_to_bends() const
{
    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position() + Point(0,-get_radius()+1);
    for (Bend bend: bends()) {
        vertices_of_links.push_back(Vertex_point(attachment));
        vertices_of_links.push_back(Vertex_point(bend.position()));
    }

    draw_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));

}

void Node::draw_links_to_first_hubs() const
{
    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position() + Point(0,get_radius()-1);

    for (Hub hub: first_hubs()) {
        vertices_of_links.push_back(Vertex_point(attachment));
        Point hub_attachment = hub.position() + Point(0,-hub.get_radius()+1);
        vertices_of_links.push_back(Vertex_point(hub_attachment));
    }

    draw_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));
}



}
