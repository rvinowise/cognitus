#include "Human_control.h"
#include <algorithm>

#include "interface/RenderingWidget.h"
#include "core/Network/Network.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"

namespace render {

using std::vector;


void Mouse_state::set_position(Point in_position) {
    position = in_position;
    world_pos = (in_position - renderingWidget->window_rect.topLeft())
            / renderingWidget->window_scale;
}
void Selection_state::set_screen_rect(Rect in_rect)
{
    screen_rect = in_rect;
    world_rect.setTopLeft(
                    Point(
                        screen_rect.left()/(renderingWidget->window_scale),
                        screen_rect.top()/(renderingWidget->window_scale)
                        )
                    );

    world_rect.setBottomRight(
                Point(
                    screen_rect.right()/(renderingWidget->window_scale),
                    screen_rect.bottom()/(renderingWidget->window_scale)
                    )
                );

    world_rect.translate(-renderingWidget->window_rect.topLeft()/renderingWidget->window_scale);

}

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
    shader_selection.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
    shader_selection.bindAttributeLocation("vertex", 0);
    shader_selection.link();
}

void Human_control::mouse_press(QMouseEvent *event)
{
    mouse_state.set_position(event->pos());
    if (event->button()==Qt::LeftButton) {
        mouse_left_press(event);
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = true;
    } else if (event->button()==Qt::MiddleButton) {
        mouse_state.middle = true;
        current_action = move_screen;
    }
}

void Human_control::mouse_left_press(QMouseEvent *event)
{
    mouse_state.left = true;

    Drawable_unit pressed_unit = get_unit_under_mouse();
    if (pressed_unit.exists()) {
        if (
                std::find(selected_units.begin(), selected_units.end(), pressed_unit)
                !=
                selected_units.end()
            ) {

        } else {
            select_only_this(pressed_unit);
            renderingWidget->update();
        }
        current_action = moving_units;
    } else {
        select_only_this(Drawable_unit::get_empty());
        current_action = selection_units;
        selection_start = event->pos();
        renderingWidget->update();
    }
}

void Human_control::mouse_move(QMouseEvent *event)
{
    Point position_delta = event->pos() - mouse_state.position;
    Point world_position_delta = position_delta/renderingWidget->window_scale;

    if (current_action == selection_units) {

        selection_state.set_screen_rect(get_selection_rect_in_screen());
        selected_units = get_units_inside_selection_rect(selection_state.world_rect);
        mark_as_selected_only_theese(selected_units);
        renderingWidget->update();
    } else if (current_action == Action::moving_units) {
        move_units(selected_units, world_position_delta);
        renderingWidget->update();
    } else if (current_action == move_screen) {
        Rect& rect = renderingWidget->window_rect;
        rect.translate(position_delta);
        renderingWidget->update();
    }

    mouse_state.set_position(event->pos());
}

void Human_control::mouse_release(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) {
        mouse_state.left = false;
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = false;
    }

    if (
            (current_action == move_screen) ||
            (current_action == selection_units)
        )
    {
        current_action = nothing;
        renderingWidget->update();
    }

}

void Human_control::mouse_wheel(QWheelEvent *event)
{
    static float scaling_step = 1.05;
    auto rotation = event->angleDelta();
    if (rotation.y() > 0) {
        renderingWidget->window_scale *= scaling_step;
    } else {
        renderingWidget->window_scale /= scaling_step;
    }
    renderingWidget->update();
}

void Human_control::key_press(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_G:
        renderingWidget->network.input.initNodes(1);
        //renderingWidget->network.input.getNode(0).generate_random_empty_figure(3);
        break;
    }
    renderingWidget->update();
}


Rect Human_control::get_selection_rect_in_screen() const
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


std::vector<Drawable_unit> Human_control::get_units_inside_selection_rect(Rect selection_in_world) const
{
    std::vector<Drawable_unit> result;
    for (Node node: renderingWidget->network) {
        vector<Drawable_unit> selected_parts = node.get_parts_inside_rect(selection_in_world);
        result.insert(result.end(), selected_parts.begin(), selected_parts.end());
        /*if (node.is_inside(selection_in_world)) {
            result.push_back(&unit);
        }*/

    }

    return result;
}

Drawable_unit Human_control::get_unit_under_mouse() const
{
    for (core::Node node: renderingWidget->network) {
        Drawable_unit pressed_part = node.get_part_under_point(mouse_state.world_pos);
        if (pressed_part.exists()) {
            return pressed_part;
        }

    }
    return Drawable_unit::get_empty();
}

void Human_control::mark_as_selected_only_theese(vector<Drawable_unit> &units)
{
    for (core::Node node: renderingWidget->network) {
        node.deselect_all_parts();
    }
    for (auto unit: units) {
        unit.select();
    }
}
void Human_control::select_only_this(Drawable_unit unit_to_select)
{
    selected_units.clear();
    for (core::Node node: renderingWidget->network) {
        node.deselect_all_parts();
    }
    if (unit_to_select.exists()) {
        selected_units.push_back(unit_to_select);
        unit_to_select.select();
    }
}


void Human_control::draw()
{
    if (current_action == selection_units) {
        draw_selection_rect();
    }
}

void Human_control::draw_selection_rect()
{
    QVector<Vertex_point> vertices_of_selection;
    vertices_of_selection.push_back(Vertex_point(selection_start));
    vertices_of_selection.push_back(Vertex_point(selection_start.x(),mouse_state.position.y()));
    vertices_of_selection.push_back(Vertex_point(mouse_state.position));
    vertices_of_selection.push_back(Vertex_point(mouse_state.position.x(),selection_start.y()));

    vao_selection_rect.bind();
    selection_vertices.bind(); //?
    selection_vertices.allocate(vertices_of_selection.constData(), vertices_of_selection.count() * sizeof(Vertex_point));
    shader_selection.bind();

    QMatrix4x4 matrix = renderingWidget->projection_matrix;
    shader_selection.setUniformValue("matrix", matrix);
    shader_selection.setUniformValue("color", QColor::fromRgbF(0,1,0.5));

    glLineWidth(2);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void Human_control::move_units(std::vector<Drawable_unit> &units, Point vector)
{
    for (auto unit: units) {
        unit.position() += vector;
    }
}




}
