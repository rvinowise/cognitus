#include "Human_control.h"
#include <algorithm>

#include "interface/RenderingWidget.h"
#include "core/Network/Network.h"
#include "core/Network/Node/Iterator/Iterator_node_BFS.h"
#include "interface/algorithms.h"

//test
#ifdef debug_mode
#include "core/Network/Node/Hub/Iterator/Iterator_BFS.h"
#include "core/test/randomFunc.h"
#include "core/test/Debug_inspector.h"
using namespace test;
#endif

namespace render {

using std::vector;


void Mouse_state::set_position(Point in_position, View_data& view_data) {
    position = in_position;
    world_pos = (in_position - view_data.window_rect.topLeft())
            / view_data.window_scale;
}
void Selection::set_screen_rect(Rect in_rect, View_data& view_data)
{
    screen_rect = in_rect;
    world_rect.setTopLeft(
                    Point(
                        screen_rect.left()/(view_data.window_scale),
                        screen_rect.top()/(view_data.window_scale)
                        )
                    );

    world_rect.setBottomRight(
                Point(
                    screen_rect.right()/(view_data.window_scale),
                    screen_rect.bottom()/(view_data.window_scale)
                    )
                );

    world_rect.translate(-view_data.window_rect.topLeft()/view_data.window_scale);

}

void Selection::Units::clear()
{
    all.clear();
    nodes.clear();
    input_nodes.clear();
    output_nodes.clear();
}

bool Selection::Units::exist()
{
    return all.size();
}


Human_control::Human_control(core::Network& in_network, Units_disposer& in_disposer):
    selection_vertices(QOpenGLBuffer::VertexBuffer),
    network{in_network},
    disposer{in_disposer}
{
    create_demo_units();
}

void Human_control::initializeGL()
{
    initializeOpenGLFunctions();
    vao_selection_rect.create();
    vao_selection_rect.bind();
    selection_vertices.create();
    selection_vertices.bind();

    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Vertex, resource_path+"shaders/selection.vert");
    shader_selection.addShaderFromSourceFile(
                QOpenGLShader::Fragment, resource_path+"shaders/selection.frag");

    shader_selection.enableAttributeArray(0);
    shader_selection.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
    shader_selection.bindAttributeLocation("vertex", 0);
    shader_selection.link();
}

void Human_control::mouse_press(QMouseEvent *event, View_data& view_data)
{
    mouse_state.set_position(event->pos(), view_data);
    if (event->button()==Qt::LeftButton) {
        mouse_left_press(event);
    } else if (event->button()==Qt::RightButton) {
        mouse_right_press(event);
    } else if (event->button()==Qt::MiddleButton) {
        mouse_state.middle = true;
        current_action = move_screen;
    }
}

void Human_control::mouse_left_press(QMouseEvent *event)
{
    mouse_state.left = true;

    Selection::Units pressed_unit = get_unit_under_mouse();

    if (pressed_unit.exist()) {
        if (!contains(selection.units.all, *pressed_unit.all.begin())) {
            select_only_this(pressed_unit);
            set_changed();
        }
        current_action = moving_units;
    } else {
        selection.units.clear();
        select_only_this(selection.units);
        current_action = selection_units;
        selection.start = event->pos();
        set_changed();
    }
}

void Human_control::mouse_right_press(QMouseEvent *event)
{

}

void Human_control::mouse_move(QMouseEvent *event, View_data& view_data)
{
    Point position_delta = event->pos() - mouse_state.position;
    Point world_position_delta = position_delta/view_data.window_scale;

    if (current_action == selection_units) {

        selection.set_screen_rect(get_selection_rect_in_screen(), view_data);
        selection.units = get_units_inside_selection_rect(selection.world_rect);
        mark_as_selected_only_theese(selection.units.all);
        set_changed();
    } else if (current_action == Action::moving_units) {
        move_units(selection.units.all, world_position_delta);
        set_changed();
    } else if (current_action == move_screen) {
        view_data.window_rect.translate(position_delta);
        set_changed();
    }

    mouse_state.set_position(event->pos(), view_data);
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
        set_changed();
    }

}

void Human_control::mouse_wheel(QWheelEvent *event, View_data& view_data)
{
    static float scaling_step = 1.05;
    auto rotation = event->angleDelta();
    if (rotation.y() > 0) {
        view_data.window_scale *= scaling_step;
    } else {
        view_data.window_scale /= scaling_step;
    }
    set_changed();
}


void Human_control::key_press(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_G:

        create_demo_units();
        break;
    case Qt::Key_F:
        fire_selected_input_nodes();
        break;
    }

    set_changed();
    debug.write_resume();
}

void Human_control::set_changed()
{
    world_changed = true;
}
void Human_control::reset_changed()
{
    world_changed = false;
}

void Human_control::create_demo_units()
{
    network.input.initNodes(100);
    auto& input = network.input;

    std::for_each(input.begin(), input.end(), [](core::Node node){
        debug.profiler.start("create units");
        node.generate_random_empty_figure(20);
        debug.profiler.stop("create units");

    });

    std::for_each(input.begin(), input.end(), [](core::Node node){
        debug.profiler.start("dispose units");
        node.dispose_hubs_into_positions();
        debug.profiler.stop("dispose units");
    });
}

void Human_control::fire_selected_input_nodes()
{
    network.input.begin_setting_input_from_outside();
    for (core::InterfaceNode input_node: selection.units.input_nodes) {
        std::size_t input_index = input_node.get_index_in_interface_array();
        network.input.prepare_wire_for_input(input_index);
    }
    network.input.end_setting_input_from_outside();

    /*ActiveBends last_active_bends = network.getLastActiveBends();
    vector<core::Bend> last_bends = last_active_bends.bends;
    for (core::Bend bend: last_bends) {*/
    network.input.wait_for_insertion_of_previous_input();
    for (core::Node node: selection.units.input_nodes) {
        disposer.dispose_last_bend(node);
    }
}


Rect Human_control::get_selection_rect_in_screen() const
{

    Point first, last;
    first.rx() = (selection.start.x() < mouse_state.position.x()) ?
            selection.start.x() : mouse_state.position.x();
    first.ry() = (selection.start.y() < mouse_state.position.y()) ?
            selection.start.y() : mouse_state.position.y();
    last.rx() = (selection.start.x() > mouse_state.position.x()) ?
            selection.start.x() : mouse_state.position.x();
    last.ry() = (selection.start.y() > mouse_state.position.y()) ?
            selection.start.y() : mouse_state.position.y();
    return Rect(first, last);
}


Selection::Units Human_control::get_units_inside_selection_rect(Rect selection_in_world) const
{
    Selection::Units selected;

    for (core::InterfaceNode node: network.input) {
        if (node.is_inside(selection_in_world)) {
            selected.all.push_back(node);
            selected.input_nodes.push_back(node);
        }
    }
    for (core::InterfaceNode node: network.output) {
        if (node.is_inside(selection_in_world)) {
            selected.all.push_back(node);
            selected.output_nodes.push_back(node);
        }
    }

    for (core::Node node: network.high_nodes()) {
        if (node.is_inside(selection_in_world)) {
            selected.all.push_back(node);
        }
    }
    for (core::Node node: network) {
        vector<Drawable_unit> selected_parts = node.get_parts_inside_rect(selection_in_world);
        selected.all.insert(selected.all.end(), selected_parts.begin(), selected_parts.end());
    }

    return selected;
}

Selection::Units Human_control::get_unit_under_mouse() const
{
    Selection::Units selected;

    for (core::InterfaceNode node: network.input) {
        if (node.has_inside(mouse_state.world_pos)) {
            selected.all.push_back(node);
            selected.input_nodes.push_back(node);
            return selected;
        }
    }
    for (core::InterfaceNode node: network.output) {
        if (node.has_inside(mouse_state.world_pos)) {
            selected.all.push_back(node);
            selected.output_nodes.push_back(node);
            return selected;
        }
    }

    for (core::Node node: network.high_nodes()) {
        if (node.has_inside(mouse_state.world_pos)) {
            selected.all.push_back(node);
            return selected;
        }
    }
    for (core::Node node: network) {
        Drawable_unit pressed_part = node.get_part_under_point(mouse_state.world_pos);
        if (pressed_part.exists()) {
            selected.all.push_back(pressed_part);
            return selected;
        }
    }

    return selected;
}


void Human_control::mark_as_selected_only_theese(vector<Drawable_unit> &units)
{
    for (core::Node node: network) {
        node.deselect_all_parts();
    }
    for (auto unit: units) {
        unit.select();
    }
}
void Human_control::select_only_this(Selection::Units& unit_to_select)
{
    for (core::Node node: network) {
        node.deselect_all_parts();
    }
    selection.units = unit_to_select;
    if (unit_to_select.all.size()) {
        unit_to_select.all.begin()->select();
    }
}


void Human_control::draw(View_data& view_data)
{
    if (current_action == selection_units) {
        draw_selection_rect(view_data);
    }
}

void Human_control::draw_selection_rect(View_data& view_data)
{
    QVector<Vertex_point> vertices_of_selection;
    vertices_of_selection.push_back(Vertex_point(selection.start));
    vertices_of_selection.push_back(Vertex_point(selection.start.x(),mouse_state.position.y()));
    vertices_of_selection.push_back(Vertex_point(mouse_state.position));
    vertices_of_selection.push_back(Vertex_point(mouse_state.position.x(),selection.start.y()));

    vao_selection_rect.bind();
    selection_vertices.bind();
    selection_vertices.allocate(vertices_of_selection.constData(), vertices_of_selection.count() * sizeof(Vertex_point));
    shader_selection.bind();

    QMatrix4x4 matrix = view_data.projection_matrix;
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
