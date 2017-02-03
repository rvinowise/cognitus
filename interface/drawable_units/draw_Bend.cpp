#include "draw_Bend.h"

#include "interface/RenderingWidget.h"


namespace render {

Bend::Bend()
{

}

int Bend::get_radius()const
{
    return 3;
}
QOpenGLTexture* Bend::get_texture()const
{
    return renderingWidget->textures[1];
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
