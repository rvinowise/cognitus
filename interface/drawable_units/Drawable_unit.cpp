#include "Drawable_unit.h"

#include "interface/functions/functions.h"
#include "interface/RenderingWidget.h"


namespace render {

using namespace pos_functions;

Drawable_unit::Drawable_unit():
    is_selected{false},
    radius{10}
{

}

void Drawable_unit::draw()
{
    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(QVector2D(position));


    //if (is_selected) {
        renderingWidget->shaders_selection.bind();
        renderingWidget->shaders_selection.setUniformValue("matrix", matrix);
        renderingWidget->shaders_selection.setUniformValue("is_selected", is_selected?1.0f:0.0f);
    /*} else {
        renderingWidget->shader_program.bind();
        renderingWidget->shader_program.setUniformValue("matrix", matrix);
    }*/
    texture->bind();
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

bool Drawable_unit::has_inside(Point point)
{
    if (poidis(position, point) < radius) {
        return true;
    }
    return false;
}

void Drawable_unit::select()
{
    is_selected = true;
}
void Drawable_unit::deselect()
{
    is_selected = false;
}


}
