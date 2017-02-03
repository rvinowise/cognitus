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


Node::Node(core::Node real_node):
    Drawable_unit(),
    node{real_node}
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

void Node::update_according_to_network()
{
    vector<core::Bend> unaccounted_real_bends =
        find_unaccounted_real_bends();
    for (core::Bend real_bend: unaccounted_real_bends) {
        add_bend_corresponding_to(real_bend);

    }

    vector<core::Hub> unaccounted_real_hubs =
            find_unaccounted_real_hubs();
    for (core::Hub real_hub: unaccounted_real_hubs) {
        add_hub_corresponding_to(real_hub);
    }


    /*bends.push_back(Bend(&(new core::Bend)));
    bends.back().position = position + Point(0, -20);
    bends.push_back(Bend());
    bends.back().position = position + Point(10, -20);
    bends.push_back(Bend());
    bends.back().position = position + Point(25, -20);*/
    /*add_first_hub();
    first_hubs.back()->position = position + Point(-10, 20);
    first_hubs.back()->add_next_hub(&(new core::Figure_bend()));
    first_hubs.back()->get_last_next_hub().position = position + Point(+40, 20);
    first_hubs.back()->add_next_hub(&(new core::Figure_bend()));
    first_hubs.back()->get_last_next_hub().position = position + Point(+40, 10);*/
}

vector<core::Bend> Node::find_unaccounted_real_bends()
{
    vector<core::Bend> result =
            get_items_of_difference(node.bends(), this->bends);
    return result;
}

vector<core::Hub> Node::find_unaccounted_real_hubs()
{
    vector<core::Hub> result =
            get_items_of_difference(node, this->hubs);
    return result;
}

void Node::add_bend_corresponding_to(core::Bend real_bend)
{
    bends.push_back(Bend(real_bend, *this));
    Point offset(0, bends.back().get_radius()+1);
    render::Bend bend = bends.back();
    render::Bend& bend_in_margin = get_unit_in_margin(bends);
    bend.position = bend_in_margin.position + offset;

}


void Node::add_hub_corresponding_to(core::Hub real_hub)
{
    hubs.push_back(Hub(real_hub, *this));
    Point offset(hubs.back().get_radius()+1,0);
    render::Hub& hub_in_margin = get_unit_in_margin(hubs);
    render::Hub hub = hubs.back();
    hub.position = hub_in_margin.position + offset;
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

bool Node::operator==(const core::Node &real_node) const
{
    return (this->node == real_node);
}


void Node::draw_links_to_bends() const
{
    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position + Point(0,-get_radius()+1);
    for (const Bend& bend: bends) {
        vertices_of_links.push_back(Vertex_point(attachment));
        vertices_of_links.push_back(Vertex_point(bend.position));
    }

    draw_link_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));

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

    draw_link_lines(vertices_of_links, Color::fromRgbF(0,0,0,0.5));
}

Hub &Node::add_first_hub(const core::Hub& real_hub)
{
    hubs.push_back(Hub(real_hub, *this));
    first_hubs.push_back(&hubs.back());
}


}
