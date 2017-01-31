#include "draw_Node.h"

#include <algorithm>

#include "core/Node/Node.h"
#include "core/Bend/Figure_bend/Figure_bend.h"
#include "core/Bend/Bend.h"
#include "core/Bend/Figure_bend/Iterator/Iterator_BFS.h"
#include "interface/RenderingWidget.h"



namespace render {

using std::vector;


Node::Node(core::Node real_node):
    Drawable_unit(),
    node{real_node}
{

}
Node::Node(const render::Node& other_node):
    Drawable_unit(),
    node{other_node.node},
    bends{other_node.bends},
    hubs{other_node.hubs},
    first_hubs{other_node.first_hubs}
{

}

int Node::get_radius() const
{
    return 10;
}
QOpenGLTexture* Node::get_texture() const
{
    return renderingWidget->textures[0];
}

void Node::update_according_to_network()
{
    for (core::Bend real_bend: node.bends()) {
        //vector<core::Bend> unaccounted_real_bends =
        //    find_unaccounted_real_bends();
    }
    for (core::Figure_bend real_hub: node) {
        vector<core::Figure_bend> unaccounted_real_hubs =
            find_unaccounted_real_hubs();
    }
    bends.push_back(Bend());
    bends.back().position = position + Point(0, -20);
    bends.push_back(Bend());
    bends.back().position = position + Point(10, -20);
    bends.push_back(Bend());
    bends.back().position = position + Point(25, -20);
    add_first_hub();
    first_hubs.back()->position = position + Point(-10, 20);
    add_next_hub(*first_hubs.back());
    first_hubs.back()->get_last_next_hub().position = position + Point(+40, 20);
    add_next_hub(*first_hubs.back());
    first_hubs.back()->get_last_next_hub().position = position + Point(+40, 10);
}

vector<core::Bend> Node::find_unaccounted_real_bends()
{
    vector<core::Bend> result;
    for (auto real_bend: node.bends()) {
        if (
                std::find(this->bends.begin(), this->bends.end(), real_bend)
                ==
                this->bends.end()
            ) {

        }
    }

}

vector<core::Figure_bend> Node::find_unaccounted_real_hubs() const
{
    vector<core::Figure_bend> result;
}

void Node::add_bend_corresponding_to(core::Bend real_bend)
{

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

Hub &Node::add_first_hub()
{
    hubs.push_back(Hub(*this));
    first_hubs.push_back(&hubs.back());
}
Hub &Node::add_next_hub(Hub& in_hub)
{
    hubs.push_back(Hub(*this));
    in_hub.next_hubs.push_back(&hubs.back());
}


}
