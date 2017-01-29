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
int Node::get_radius()
{
    return 10;
}
QOpenGLTexture* Node::get_texture()
{
    return renderingWidget->textures[0];
}

void Node::update_according_to_network()
{
    for (core::Bend real_bend: node.bends()) {
        vector<core::Bend> unaccounted_real_bends =
            find_unaccounted_real_bends();
    }
    for (core::Figure_bend real_hub: node) {

    }
    bends.push_back(Bend());
    bends.back().position = position + Point(0, -20);
    hubs.push_back(Hub());
    hubs.back().position = position + Point(-10, 20);
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

void Node::draw()
{
    std::for_each(bends.begin(), bends.end(), [](Bend& bend){bend.draw();});
    std::for_each(hubs.begin(), hubs.end(), [](Hub& hub){hub.draw();});
    Drawable_unit::draw();
}



}
