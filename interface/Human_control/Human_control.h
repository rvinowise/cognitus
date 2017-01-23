#pragma once

#include <QtCore>
#include <QMouseEvent>
#include <vector>

namespace render {

struct Mouse_state
{
    bool left;
    bool right;
    QVector2D position;
};
enum Action
{
    select_units,
    move_units
};

class Human_control
{
public:
    Human_control();

    void mouse_press(QMouseEvent *event);
    void mouse_left_press(QMouseEvent *event);
    void mouse_right_press(QMouseEvent *event);
    void mouse_move(QMouseEvent *event);
    void mouse_release(QMouseEvent *event);


private:
    std::vector<Drawable_unit> get_units_under_mouse();
    void draw_selection_rect();

    Mouse_state mouse_state;
    Action current_action;

    QVector2D selection_start;
    std::vector<Drawable_unit> selected_units;
    std::vector<Drawable_unit> pressed_units;
};

}
