#pragma once

#include <QtCore>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <vector>

#include "interface/drawable_units/Drawable_unit.h"


namespace render {

using Point = QPoint;
using Rect = QRect;

struct Mouse_state
{
    bool left;
    bool right;
    bool middle;
    Point position;
    Point world_pos;
};
enum Action
{
    nothing,
    select_units,
    move_units,
    move_screen
};

class Human_control: protected QOpenGLFunctions
{
public:
    Human_control();
    void initializeGL();

    void mouse_press(QMouseEvent *event);
    void mouse_left_press(QMouseEvent *event);
    void mouse_right_press(QMouseEvent *event);
    void mouse_move(QMouseEvent *event);
    void mouse_release(QMouseEvent *event);

    void draw();

    Rect calculate_selection_rect();
private:
    std::vector<Drawable_unit> get_units_under_mouse();
    std::vector<Drawable_unit> get_units_inside_selection_rect();
    void draw_selection_rect();

    Mouse_state mouse_state;
    Action current_action;

    Point selection_start;
    QRect selection_rect;


    std::vector<Drawable_unit> selected_units;
    std::vector<Drawable_unit> pressed_units;

//protected:
    QOpenGLBuffer selection_vertices;
    QOpenGLVertexArrayObject vao_selection_rect;
    QOpenGLShaderProgram shader_selection;
};

}
