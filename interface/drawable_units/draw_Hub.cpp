#include "draw_Hub.h"

#include "interface/RenderingWidget.h"

#include "draw_Node.h"
namespace render {


/*Hub::Hub():
    node{nullptr}
{

}*/

Hub::Hub(Node &in_node):
    Drawable_unit(),
    node(in_node)
{

}

Hub::Hub(const Hub &other_hub):
    node(other_hub.node)
{

}


int Hub::get_radius() const
{
    return 4;
}
QOpenGLTexture* Hub::get_texture() const
{
    return renderingWidget->textures[2];
}

Color Hub::get_links_to_next_hubs_color() const
{
    return Color::fromRgbF(0,0,0,0.5);
}

Hub &Hub::get_last_next_hub()
{
    return *this->next_hubs.back();
}

void Hub::draw_links_to_next_hubs() const
{

    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position + Point(get_radius()-1,0);

    for (render::Hub* next_hub: this->next_hubs) {
        vertices_of_links.push_back(Vertex_point(attachment));
        Point hub_attachment = next_hub->position + Point(-next_hub->get_radius()+1,0);
        vertices_of_links.push_back(Vertex_point(hub_attachment));
    }

    draw_link_lines(vertices_of_links, get_links_to_next_hubs_color());

}

Hub &Hub::add_next_hub()
{
    node.hubs.push_back(Hub(node));
    //node.first_hubs.push_back(new Hub(*this));
    std::size_t lol = node.first_hubs.size();
    std::size_t lol1 = node.hubs.size();
    next_hubs.push_back(node.first_hubs.back());
    return node.hubs.back();
}

void Hub::update_according_to_network()
{

}

void Hub::draw() const
{
    Drawable_unit::draw();
    draw_links_to_next_hubs();
}



}
