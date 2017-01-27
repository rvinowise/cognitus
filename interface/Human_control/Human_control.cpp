#include "Human_control.h"

#include "interface/RenderingWidget.h"

namespace render {

Human_control::Human_control():
    selection_vertices(QOpenGLBuffer::VertexBuffer)
{

}

void Human_control::initializeGL()
{
    initializeOpenGLFunctions();
    vao_selection_rect.create();
    vao_selection_rect.bind();
    selection_vertices.create();
    selection_vertices.bind();

    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Vertex, RenderingWidget::resource_path+"shaders/selection.vert");
    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Fragment, RenderingWidget::resource_path+"shaders/selection.frag");

    shader_selection.enableAttributeArray(0);
    shader_selection.setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
    shader_selection.bindAttributeLocation("vertex", 0);
    shader_selection.link();
}

void Human_control::mouse_press(QMouseEvent *event)
{

    if (event->button()==Qt::LeftButton) {
        mouse_left_press(event);
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = true;
    } else if (event->button()==Qt::MiddleButton) {
        mouse_state.middle = true;
        current_action = move_screen;
        mouse_state.position = event->pos();
    }
}

void Human_control::mouse_left_press(QMouseEvent *event)
{
    mouse_state.left = true;

    pressed_units = get_units_under_mouse();

    if (selected_units.empty()) {
        current_action = select_units;
        selection_start = event->pos();
    } else {
        current_action = move_units;
    }
}

void Human_control::mouse_move(QMouseEvent *event)
{
    if (current_action == select_units) {
        //find_selected_units();
        selection_rect = calculate_selection_rect();
        get_units_inside_selection_rect();
        qDebug() << "move_selection";
        renderingWidget->update();

    } else if (current_action == move_units) {
        //move_selected_units();
    } else if (current_action == move_screen) {
        //move_selected_units();
        //QMatrix4x4& matrix = renderingWidget->projection_matrix;
        Rect& rect = renderingWidget->window_rect;
        rect.translate(
                    event->x() - mouse_state.position.x()
                    ,
                    event->y() - mouse_state.position.y()
                    );
        renderingWidget->update();
    }

    mouse_state.position = event->pos();
    //mouse_state.world_pos =


    //qDebug() << "x:" << mouse_state.position.x() << "y:" << mouse_state.position.y();
}

void Human_control::mouse_release(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) {
        mouse_state.left = false;
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = false;
    }

    if (current_action == move_screen) {
        current_action = nothing;
    }
}

Rect Human_control::calculate_selection_rect()
{

    Point first, last;
    first.rx() = (selection_start.x() < mouse_state.position.x()) ?
            selection_start.x() : mouse_state.position.x();
    first.ry() = (selection_start.y() < mouse_state.position.y()) ?
            selection_start.y() : mouse_state.position.y();
    last.rx() = (selection_start.x() > mouse_state.position.x()) ?
            selection_start.x() : mouse_state.position.x();
    last.ry() = (selection_start.y() > mouse_state.position.y()) ?
            selection_start.y() : mouse_state.position.y();
    return Rect(first, last);
}


std::vector<Drawable_unit> Human_control::get_units_inside_selection_rect()
{
    if (
        (selection_rect.width() > 400) &&
        (selection_rect.height() > 400)
            ) {
        bool test = true;
    }

    std::vector<Drawable_unit> result;
    for (Drawable_unit unit: renderingWidget->units) {
        if (unit.is_inside(selection_rect)) {
            result.push_back(unit);
            unit.is_selected = true;
        }

    }

    return result;
}


std::vector<Drawable_unit> Human_control::get_units_under_mouse()
{
    std::vector<Drawable_unit> result;
    //for () {

    //}

    return result;
}


void Human_control::draw()
{
    if (current_action == select_units) {
        draw_selection_rect();
    }
}

void Human_control::draw_selection_rect()
{
    //qDebug() << "draw_selection_rect";
    QVector<Vertex> vertices;
    vertices.push_back(Vertex{ selection_start.x(),selection_start.y(),0,0});
    vertices.push_back(Vertex{ selection_start.x(),mouse_state.position.y(),0,0});
    vertices.push_back(Vertex{ mouse_state.position.x(),mouse_state.position.y(),0,0});
    vertices.push_back(Vertex{ mouse_state.position.x(),selection_start.y(),0,0});

    vao_selection_rect.bind();
    selection_vertices.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));
    shader_selection.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    shader_selection.setUniformValue("matrix", matrix);

    glLineWidth(2);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}


}
