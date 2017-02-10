#include "Drawable_unit.h"

#include "interface/functions/functions.h"
#include "interface/RenderingWidget.h"

#include "interface/primitives/Rectangle/Rectangle.h"
#include "interface/primitives/Vertex/Vertex.h"


namespace render {

using namespace pos_functions;

Drawable_unit_data::Drawable_unit_data():
    is_selected{false}
{

}


Drawable_unit::Drawable_unit():
    data{nullptr}
{
}
Drawable_unit::Drawable_unit(const Drawable_unit &other)
{
    data = other.data;
}
Drawable_unit::Drawable_unit(Drawable_unit &&other)
{
    data = other.data;
    other.data = nullptr;
}

Drawable_unit::~Drawable_unit()
{
    if (data) {
        //handle disconnect
    }
}

void Drawable_unit::create_data()
{
    data = new Drawable_unit_data();
}

bool Drawable_unit::operator==(const Drawable_unit& other) const
{
    return data==other.data;
}

bool Drawable_unit::operator=(const Drawable_unit &other)
{
    data=other.data;
}

Drawable_unit Drawable_unit::get_empty()
{
    return Drawable_unit();
}

bool Drawable_unit::is_empty() const
{
    return !data;
}

bool Drawable_unit::exists() const
{
    return data;
}


void Drawable_unit::draw() const
{
    Rectangle::vao_rect.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(QVector2D(position()));
    matrix.scale(get_radius()/sprite_etalon_radius);

    Sprite::shaders.bind();
    Sprite::shaders.setUniformValue("matrix", matrix);
    Sprite::shaders.setUniformValue("is_selected", is_selected()?1.0f:0.0f);
    get_texture()->bind();

    Sprite::draw();
}

void Drawable_unit::draw_link_to(const Drawable_unit &other) const
{

}

bool Drawable_unit::is_inside(Rect rect) const
{
    Point first = rect.topLeft();
    Point last = rect.bottomRight();
    if (
            (first.x() < position().x()) &&
            (first.y() < position().y()) &&
            (last.x() > position().x()) &&
            (last.y() > position().y())
       )
    {
        return true;
    }
    return false;
}

bool Drawable_unit::has_inside(Point point) const
{
    if (poidis(position(), point) < get_radius()) {
        return true;
    }
    return false;
}

void Drawable_unit::select()
{
    data->is_selected = true;
}
void Drawable_unit::deselect()
{
    data->is_selected = false;
}

bool Drawable_unit::is_selected() const
{
    return data->is_selected;
}

Point &Drawable_unit::position()
{
    return data->position;
}

Point Drawable_unit::position() const
{
    return data->position;
}

int Drawable_unit::get_radius()const
{
    throw("Drawable_unit::get_radius()");
    return 0;
}

QOpenGLTexture *Drawable_unit::get_texture() const
{
    return 0;
}



void Drawable_unit::draw_lines(
        const std::vector<Vertex_point>& vertices,
        const Color& color) const
{
    renderingWidget->vao_link_lines.bind();
    renderingWidget->link_lines_buffer.bind();
    renderingWidget->link_lines_buffer.allocate(vertices.data(), vertices.size() * sizeof(Vertex_point));
    renderingWidget->shaders_link_lines.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    renderingWidget->shaders_link_lines.setUniformValue("matrix", matrix);
    renderingWidget->shaders_link_lines.setUniformValue("color", color);
    renderingWidget->draw_lines(vertices.size());
}

void Drawable_unit::draw_lines(const std::vector<Vertex_colored> &vertices) const
{
    renderingWidget->vao_link_lines.bind();
    renderingWidget->link_lines_buffer.bind();
    renderingWidget->link_lines_buffer.allocate(vertices.data(), vertices.size() * sizeof(Vertex_colored));
    renderingWidget->shaders_link_lines.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    renderingWidget->shaders_link_lines.setUniformValue("matrix", matrix);
    renderingWidget->draw_lines(vertices.size());
}




}
