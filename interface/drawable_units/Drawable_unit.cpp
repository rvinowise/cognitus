#include "Drawable_unit.h"

#include "interface/RenderingWidget.h"


namespace render {

Drawable_unit::Drawable_unit():
    is_selected{false}
{

}

void Drawable_unit::draw()
{
    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(QVector2D(position));
    renderingWidget->shader_program.setUniformValue("matrix", matrix);

    if (is_selected) {
        renderingWidget->textures[1]->bind();
    } else {
        texture->bind();
    }
    renderingWidget->draw_unit_rect();

}

void Drawable_unit::draw_link_to(const Drawable_unit &other)
{

}

bool Drawable_unit::is_inside(Rect rect)
{
    Point first = rect.topLeft();
    Point last = rect.bottomRight();
    if (
            (first.x() < position.x()) &&
            (first.y() < position.y()) &&
            (last.x() > position.x()) &&
            (last.y() > position.y())
       )
    {
        return true;
    }
    return false;
}


}
