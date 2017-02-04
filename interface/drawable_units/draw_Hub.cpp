#include "draw_Hub.h"

#include "interface/RenderingWidget.h"

#include "draw_Node.h"
namespace render {




Hub::Hub()
{

}


int Hub::get_radius()const
{
    return 4;
}
QOpenGLTexture* Hub::get_texture()const
{
    return renderingWidget->textures[2];
}

Color Hub::get_links_to_next_hubs_color() const
{
    return Color::fromRgbF(0,0,0,0.5);
}



void Hub::draw_links_to_next_hubs() const
{

    std::vector<Vertex_point> vertices_of_links;
    Point attachment = this->position + Point(get_radius()-1,0);

    for (render::Hub* next_hub: this->get_arr_next_hubs()) {
        vertices_of_links.push_back(Vertex_point(attachment));
        Point hub_attachment = next_hub->position + Point(-next_hub->get_radius()+1,0);
        vertices_of_links.push_back(Vertex_point(hub_attachment));
    }

    draw_lines(vertices_of_links, get_links_to_next_hubs_color());

}


void Hub::draw() const
{
    Drawable_unit::draw();
    draw_links_to_next_hubs();
}



}
