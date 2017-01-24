#include "Human_control.h"

#include "interface/RenderingWidget.h"

namespace render {

Human_control::Human_control()
{
    selection_vertices.create();
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
    } else if (current_action == move_units) {
        //move_selected_units();
    } else if (current_action == move_screen) {
        //move_selected_units();
        //QMatrix4x4& matrix = renderingWidget->projection_matrix;
        QRectF& rect = renderingWidget->window_rect;
        rect.translate(
                    event->x() - mouse_state.position.x()
                    ,
                    event->y() - mouse_state.position.y()
                    );
        renderingWidget->update();
    }

    mouse_state.position = event->pos();
    //mouse_state.world_pos =

    qDebug() << "x:" << mouse_state.position.x() << "y:" << mouse_state.position.y();
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



std::vector<Drawable_unit> Human_control::get_units_under_mouse()
{
    std::vector<Drawable_unit> result;
    //for () {

    //}

    return result;
}


void Human_control::draw()
{
    draw_selection_rect();
}

void Human_control::draw_selection_rect()
{
    QVector<Vertex> vertices;
    /*vertices.push_back(Vertex{ selection_start.x(),selection_start.y(),0,0});
    vertices.push_back(Vertex{ selection_start.x(),mouse_state.position.y(),0,0});
    vertices.push_back(Vertex{ mouse_state.position.x(),mouse_state.position.y(),0,0});
    vertices.push_back(Vertex{ mouse_state.position.x(),selection_start.y(),0,0});*/
    vertices.push_back(Vertex{ 0,0,0,0});
        vertices.push_back(Vertex{ 0,mouse_state.position.y(),0,0});
        vertices.push_back(Vertex{ mouse_state.position.x(),mouse_state.position.y(),0,0});
        vertices.push_back(Vertex{ mouse_state.position.x(),0,0,0});

    selection_vertices.create();
    selection_vertices.bind();
    selection_vertices.allocate(vertices.constData(), vertices.count() * sizeof(Vertex));

    //QMatrix4x4 matrix = renderingWidget->projection_matrix;
    //matrix.translate(selection_start.x(), selection_start.y());
    //renderingWidget->shader_program.setUniformValue("matrix", matrix);

    renderingWidget->textures[0]->bind();
    renderingWidget->draw_unit_rect();
}


}
