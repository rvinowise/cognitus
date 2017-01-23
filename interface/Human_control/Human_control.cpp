#include "Human_control.h"

namespace render {

Human_control::Human_control()
{

}

void Human_control::mouse_press(QMouseEvent *event)
{

    if (event->button()==Qt::LeftButton) {
        mouse_left_press(event);
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = true;
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
    mouse_state.position = event->pos();
    if (current_action == select_units) {
        find_selected_units();
    } else if (current_action == move_units) {
        move_selected_units();
    }
}

void Human_control::mouse_release(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) {
        mouse_state.left = false;
    } else if (event->button()==Qt::RightButton) {
        mouse_state.right = false;
    }
}

std::vector<Drawable_unit> Human_control::get_units_under_mouse()
{
    std::vector<Drawable_unit> result;
    for () {

    }
}


}
