#include "draw_Hub.h"

#include "interface/RenderingWidget.h"

#include "draw_Node.h"
#include "core/Network/Node/Hub/Hub.h"
#include "core/test/Debug_inspector.h"


namespace render {




Hub::Hub():
    Drawable_unit()
{
}
Hub::Hub(const Hub &other):
    Drawable_unit(other)
{
}
Hub::Hub(Hub &&other):
    Drawable_unit(std::move(other))
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

    std::vector<Vertex_colored> vertices_of_links;
    Point attachment = this->position() + Point(get_radius()-1,0);
    Color color_link = Color::fromRgbF(0,0,0,0.5);
    Color color_begin = (is_selected() ? /*color_link+*/selection_color : color_link);
    for (core::Hub next_hub: this->get_arr_next_hubs()) {
        vertices_of_links.push_back(Vertex_colored(attachment, color_begin));
        Point hub_attachment = next_hub.position() + Point(-next_hub.get_radius()+1,0);
        Color color_end = (next_hub.is_selected() ? /*color_link+*/selection_color : color_link);
        vertices_of_links.push_back(Vertex_colored(hub_attachment, color_end));
    }

    draw_lines(vertices_of_links);

}


void Hub::draw() const
{
    Drawable_unit::draw();
    //draw_links_to_next_hubs();
}



}
