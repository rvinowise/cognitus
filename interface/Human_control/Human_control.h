#pragma once

#include <QtCore>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <vector>

#include "interface/drawable_units/Drawable_unit.h"
#include "interface/coordinates_type.h"

namespace render {



struct Mouse_state
{
    bool left;
    bool right;
    bool middle;
    Point position;
    Point world_pos;

    void set_position(Point);
};
struct Selection_state
{
    Rect screen_rect;
    Rect world_rect;

    void set_screen_rect(Rect in_rect);
};

enum Action
{
    nothing,
    selection_units,
    moving_units,
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
    void mouse_wheel(QWheelEvent *event);
    void key_press(QKeyEvent *event);

    void draw();


private:
    Drawable_unit* get_unit_under_mouse() const;
    std::vector<Drawable_unit*> get_units_inside_selection_rect(Rect selection_in_world) const;
    Rect get_selection_rect_in_screen() const;
    void mark_as_selected_only_theese(std::vector<Drawable_unit *> &units);
    void select_only_this(Drawable_unit* unit);
    void draw_selection_rect();
    void move_units(std::vector<Drawable_unit *>& units, Point vector);

    Mouse_state mouse_state;
    Selection_state selection_state;
    Action current_action;

    Point selection_start;

    std::vector<Drawable_unit*> selected_units;
    //std::vector<Drawable_unit&> pressed_units;

//protected:
    QOpenGLBuffer selection_vertices;
    QOpenGLVertexArrayObject vao_selection_rect;
    QOpenGLShaderProgram shader_selection;
};

}
