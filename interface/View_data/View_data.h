#pragma once

#include <QMatrix4x4>

#include "interface/common/coordinates_type.h"

namespace render {

struct View_data
{
    View_data():
        window_scale{1}
    {

    }
    QMatrix4x4 projection_matrix;
    float window_scale;
    Rect window_rect;
};

}
