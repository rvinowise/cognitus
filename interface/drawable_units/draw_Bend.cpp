#include "draw_Bend.h"

#include "interface/RenderingWidget.h"

#include "core/Network/Node/Bend/Bend.h"

namespace render {

Bend::Bend():
    Drawable_unit()
{
}
Bend::Bend(const Bend &other):
    Drawable_unit(other)
{
}
Bend::Bend(Bend &&other):
    Drawable_unit(std::move(other))
{
}
render::Bend Bend::operator=(const Bend &other)
{
    data = other.data;
}

int Bend::get_radius()const
{
    return 3;
}
QOpenGLTexture* Bend::get_texture()const
{
    return renderingWidget->textures[1];
}

std::vector<core::Bend> &Bend::get_array_of_next_bends()
{
    throw_msg("render::Bend get_array_of_next_bends must call the function of core::Bend");
}


Color Bend::get_links_to_next_bends_color() const
{
    return Color::fromRgbF(0,0,0,0.5);
}

void Bend::draw()
{
    Drawable_unit::draw();
    draw_links_to_next_bends();
}

void Bend::draw_links_to_next_bends()
{

    std::vector<Vertex_point> vertices_of_links;

    for (render::Bend next_bend: this->get_array_of_next_bends()) {
        vertices_of_links.push_back(Vertex_point(position()));
        vertices_of_links.push_back(Vertex_point(next_bend.position()));
    }

    draw_lines(vertices_of_links, get_links_to_next_bends_color());

}



}
