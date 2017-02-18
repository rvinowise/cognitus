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
    for (const core::Bend next_bend: this->next_bends()) {
        link_vertices.emplace_back(Vertex_colored(position(), color_begin));
        Color color_end = (next_bend.is_selected() ? /*color_link+*/selection_color : color_link);
        link_vertices.emplace_back(Vertex_colored(next_bend.position(), color_end));

        float direction_to_next = poidir(position(), next_bend.position());
        arrow_vectors.emplace_back(Arrow_vector{next_bend.position(), direction_to_next});
    }
}



}
