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




void Bend::draw()
{
    Drawable_unit::draw();
    draw_links_to_next_bends();
    draw_arrows();
}

void Bend::draw_links_to_next_bends()
{

    std::vector<Vertex_point> vertices_of_links;

    for (core::Bend next_bend: this->get_array_of_next_bends()) {
        vertices_of_links.push_back(Vertex_point(position()));
        vertices_of_links.push_back(Vertex_point(next_bend.position()));
    }

    draw_lines(vertices_of_links, get_links_to_next_bends_color());

}

void Bend::draw_arrows() {
    Arrow::vao_rect.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(QVector2D(position()+Point(0,-10)));
    matrix.scale(get_radius()/sprite_etalon_radius);

    Arrow::shaders.bind();
    Arrow::shaders.setUniformValue("matrix", matrix);
    //Arrow::shaders.setUniformValue("is_selected", is_selected()?1.0f:0.0f);
    Arrow::shaders.setUniformValue("color", Color::fromRgbF(1,0,0,1));

    Arrow::draw();
}



}
