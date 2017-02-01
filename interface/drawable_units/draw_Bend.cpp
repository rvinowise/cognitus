#include "draw_Bend.h"

#include "interface/RenderingWidget.h"


namespace render {

Bend::Bend(core::Bend real_bend, render::Node &in_node):
    Drawable_unit(),
    bend{real_bend},
    node{in_node}
{

}

int Bend::get_radius()
{
    return 3;
}
QOpenGLTexture* Bend::get_texture()
{
    return renderingWidget->textures[1];
}

bool Bend::operator ==(const core::Bend &real_bend) const
{
    return (this->bend == real_bend);
}

Color Bend::get_links_to_next_bends_color() const
{
    return Color::fromRgbF(0,0,0,0.5);
}

void Bend::draw() const
{
    Drawable_unit::draw();
    draw_links_to_next_bends();
}

void Bend::draw_links_to_next_bends() const
{

    std::vector<Vertex_point> vertices_of_links;

    for (render::Bend* next_bend: this->next_bends) {
        vertices_of_links.push_back(Vertex_point(position));
        vertices_of_links.push_back(Vertex_point(next_bend->position));
    }

    draw_link_lines(vertices_of_links, get_links_to_next_bends_color());

}



}
