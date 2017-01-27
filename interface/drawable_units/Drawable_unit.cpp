#include "Drawable_unit.h"

#include "interface/RenderingWidget.h"


namespace render {

Drawable_unit::Drawable_unit()
{

}

void Drawable_unit::draw()
{
    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    matrix.translate(position);
    renderingWidget->shader_program.setUniformValue("matrix", matrix);
    renderingWidget->shader_selection.setUniformValue("matrix", matrix);

    texture->bind();
    renderingWidget->draw_unit_rect();

}

void Drawable_unit::draw_link_to(const Drawable_unit &other)
{

}


}
