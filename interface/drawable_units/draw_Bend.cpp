#include "draw_Bend.h"

#include "interface/RenderingWidget.h"

#include "core/Network/Node/Bend/Bend.h"
#include "interface/functions/functions.h"



namespace render {


using namespace pos_functions;

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

const float Bend::radius = 3;
int Bend::get_radius()const
{
    return radius;
}
QOpenGLTexture* Bend::get_texture()
{
    return Sprite::textures[1];
}



void Bend::prepare_draw_data(Shared_drawn_data &drawn_data) const
{
    auto& link_vertices = drawn_data.vertices;
    auto& arrow_vectors = drawn_data.arrow_vectors;
    Color color_link = Color::fromRgbF(0,0,0,0.5);
    Color color_begin = (is_selected() ? /*color_link+*/selection_color : color_link);
    for (const core::Bend next_bend: this->get_array_of_next_bends()) {
        link_vertices.push_back(Vertex_colored(position(), color_begin));
        Color color_end = (next_bend.is_selected() ? /*color_link+*/selection_color : color_link);
        link_vertices.push_back(Vertex_colored(next_bend.position(), color_end));

        float direction_to_next = poidir(position(), next_bend.position());
        arrow_vectors.push_back(Arrow_vector{next_bend.position(), direction_to_next});
    }
}

/*void Bend::prepare_draw_data_of_arrows(std::vector<Arrow_vector> &vectors) const
{
    for (core::Bend next_bend: this->get_array_of_next_bends()) {
        vertices_of_links.push_back(Vertex_colored(position(), color_begin));
        Color color_end = (next_bend.is_selected() ? color_link+selection_color : color_link);
        vertices_of_links.push_back(Vertex_colored(next_bend.position(), color_end));

        QMatrix4x4 matrix = renderingWidget->projection_matrix;
        matrix.translate(QVector2D(next_bend.position()));
        float direction_to_next = poidir(position(), next_bend.position());
        matrix.rotate(direction_to_next,0,0,1);
        Arrow::shaders.setUniformValue("matrix", matrix);
        Arrow::draw();
    }
}
*/

/*void Bend::draw_links_to_next_bends() const
{
    Arrow::vertex_array.bind();


    Arrow::shaders.bind();

    Arrow::shaders.setUniformValue("color", Color::fromRgbF(0,0,0,0.5));

    std::vector<Vertex_colored> vertices_of_links;
    Color color_link = Color::fromRgbF(0,0,0,0.5);
    Color color_begin = (is_selected() ? color_link+selection_color : color_link);
    for (core::Bend next_bend: this->get_array_of_next_bends()) {
        vertices_of_links.push_back(Vertex_colored(position(), color_begin));
        Color color_end = (next_bend.is_selected() ? color_link+selection_color : color_link);
        vertices_of_links.push_back(Vertex_colored(next_bend.position(), color_end));

        QMatrix4x4 matrix = renderingWidget->projection_matrix;
        matrix.translate(QVector2D(next_bend.position()));
        float direction_to_next = poidir(position(), next_bend.position());
        matrix.rotate(direction_to_next,0,0,1);
        Arrow::shaders.setUniformValue("matrix", matrix);
        Arrow::draw();
    }

    draw_lines(vertices_of_links);

}

void Bend::draw_arrows() {
    Arrow::vertex_array.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(QVector2D(position()+Point(0,-10)));
    matrix.scale(get_radius()/sprite_etalon_radius);

    Arrow::shaders.bind();
    Arrow::shaders.setUniformValue("matrix", matrix);
    //Arrow::shaders.setUniformValue("is_selected", is_selected()?1.0f:0.0f);
    Arrow::shaders.setUniformValue("color", Color::fromRgbF(0,0,0,0.5));

    Arrow::draw();
}*/



}
