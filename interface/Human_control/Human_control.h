#pragma once

#include <QtCore>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <vector>

//#include "interface/drawable_units/Drawable_unit.h"
#include "interface/common/constants.h"
#include "core/Network/Node/InterfaceNode.h"
#include "interface/View_data/View_data.h"
#include "interface/Units_disposer/Units_disposer.h"

namespace core {
    class Network;
}

namespace render {

class Drawable_unit;

struct Mouse_state
{
    bool left;
    bool right;
    bool middle;
    Point position;
    Point world_pos;

    void set_position(Point, View_data &view_data);
};
struct Selection
{
    Point start;
    Rect screen_rect;
    Rect world_rect;
    void set_screen_rect(Rect in_rect, View_data &view_data);

    struct Units
    {
        std::vector<Drawable_unit> all;
        std::vector<core::Node> nodes;
        std::vector<core::InterfaceNode> input_nodes;
        std::vector<core::InterfaceNode> output_nodes;

        std::vector<core::InterfaceNode> get_interface_nodes();

        void clear();
        bool exist();
    } units;
};

enum class Action
{
    nothing,
    selection_units,
    moving_units,
    move_screen
};



class Human_control: protected QOpenGLFunctions
{
public:
    Human_control(core::Network& in_network, 
                  Units_disposer& in_disposer,
                  View_data& in_view_data);
    void initializeGL();

    void mouse_press(QMouseEvent *event);
    void mouse_left_press(QMouseEvent *event);
    void mouse_right_press(QMouseEvent *event);
    void mouse_move(QMouseEvent *event);
    void mouse_release(QMouseEvent *event);
    void mouse_wheel(QWheelEvent *event);
    void key_press(QKeyEvent *event);

    bool world_changed;
    void set_changed();
    void reset_changed();
    void draw();


private:
    Selection::Units get_unit_under_mouse() const;
    Selection::Units get_units_inside_selection_rect(Rect selection_in_world) const;
    Rect get_selection_rect_in_screen() const;
    void mark_as_selected_only_theese(std::vector<Drawable_unit> &units);
    void select_only_this(Selection::Units &unit);
    void draw_selection_rect();
    void move_units(std::vector<Drawable_unit> &units, Point vector);
    void create_demo_units();
    void fire_selected_input_nodes();

    Mouse_state mouse_state;
    Selection selection;
    Action current_action;



protected:
    QOpenGLVertexArrayObject vao_selection_rect;
    QOpenGLBuffer selection_vertices;
    QOpenGLShaderProgram shader_selection;

    Units_disposer& disposer;
    core::Network& network;
    View_data& view_data;
};

}
