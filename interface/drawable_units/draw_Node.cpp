#include "draw_Node.h"

#include <algorithm>

#include "core/Network/Node/Node.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/Network/Node/Bend/Bend.h"
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "interface/RenderingWidget.h"
#include "interface/algorithms.h"


namespace render {

using std::vector;


int Node::get_radius()const
{
    return 10;
}
QOpenGLTexture* Node::get_texture()const
{
    return renderingWidget->textures[0];
}


vector<Drawable_unit *> Node::get_parts_inside_rect(Rect rect)
{
    vector<Drawable_unit*> result;
    if (is_inside(rect)) {
        result.push_back(this);
    }
    for (Bend& bend: bends) {
        if (bend.is_inside(rect)) {
            result.push_back(&bend);
        }
    }
    for (Hub& hub: hubs) {
        if (hub.is_inside(rect)) {
            result.push_back(&hub);
        }
    }
    return result;
}

Drawable_unit *Node::get_part_under_point(Point point)
{
    if (has_inside(point)) {
        return this;
    }
    for (Bend& bend: bends) {
        if (bend.has_inside(point)) {
            return &bend;
        }
    }
    for (Hub& hub: hubs) {
        if (hub.has_inside(point)) {
            return &hub;
        }
    }
    return nullptr;
}

void Node::deselect_all_parts()
{
    deselect();
    for (Bend& bend: bends) {
        bend.deselect();
    }
    for (Hub& hub: hubs) {
        hub.deselect();
    }
}

void Node::draw() const
{
    std::for_each(bends.begin(), bends.end(), [](const Bend& bend){bend.draw();});
    std::for_each(hubs.begin(), hubs.end(), [](const Hub& hub){hub.draw();});
    Drawable_unit::draw();

    draw_links_to_first_hubs();
    draw_links_to_bends();
}



void Node::draw_links_to_bends() const
{
    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position + Point(0,-get_radius()+1);
    for (const Bend& bend: bends) {
        vertices_of_links.push_back(Vertex_point(attachment));
        vertices_of_links.push_back(Vertex_point(bend.position));
    }

    draw_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));

}

void Node::draw_links_to_first_hubs() const
{
    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position + Point(0,get_radius()-1);

    for (const Hub* hub: first_hubs) {
        vertices_of_links.push_back(Vertex_point(attachment));
        Point hub_attachment = hub->position + Point(0,-hub->get_radius()+1);
        vertices_of_links.push_back(Vertex_point(hub_attachment));
    }

    draw_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));
}

Hub &Node::add_first_hub(const core::Hub& real_hub)
{
    hubs.push_back(Hub(real_hub, *this));
    first_hubs.push_back(&hubs.back());
}


}
