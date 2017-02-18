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


const float Hub::radius = 4;
int Hub::get_radius()const
{
    return 4;
}
QOpenGLTexture* Hub::get_texture()
{
    return Sprite::textures[2];
}

Color Hub::get_links_to_next_hubs_color() const
{
    return Color::fromRgbF(0,0,0,0.5);
}



void Hub::prepare_draw_data(std::vector<Vertex_colored>& vertices) const
{
    Point attachment = this->position() + Point(get_radius()-1,0);
    Color color_link = Color::fromRgbF(0,0,0,0.5);
    Color color_begin = (is_selected() ? /*color_link+*/selection_color : color_link);
    for (core::Hub next_hub: this->get_arr_next_hubs()) {
        vertices.emplace_back(Vertex_colored(attachment, color_begin));
        Point hub_attachment = next_hub.position() + Point(-next_hub.get_radius()+1,0);
        Color color_end = (next_hub.is_selected() ? /*color_link+*/selection_color : color_link);
        vertices.emplace_back(Vertex_colored(hub_attachment, color_end));
    }

    attachment = this->position() + Point(0, get_radius());
    for (core::Bend bend: this->bends()) {
        vertices.emplace_back(Vertex_colored(attachment, color_begin));
        Point bend_attachment = bend.position() + Point(0,-bend.get_radius());
        Color color_end = (bend.is_selected() ? /*color_link+*/selection_color : color_link);
        vertices.emplace_back(Vertex_colored(bend_attachment, color_end));
    }
}



}
