#pragma once

#include <QtCore>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <vector>

#include "interface/drawable_units/Drawable_unit.h"


namespace render {

using Point = QPointF;

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

    void mouse_press(QMouseEvent *event);
    void mouse_left_press(QMouseEvent *event);
    void mouse_right_press(QMouseEvent *event);
    void mouse_move(QMouseEvent *event);
    void mouse_release(QMouseEvent *event);

    void draw();

    QOpenGLBuffer selection_vertices;
private:
    std::vector<Drawable_unit> get_units_under_mouse();
    void draw_selection_rect();

    Mouse_state mouse_state;
    Action current_action;

    Point selection_start;
    std::vector<Drawable_unit> selected_units;
    std::vector<Drawable_unit> pressed_units;
};

}
