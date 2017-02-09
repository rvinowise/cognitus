#pragma once

#include <QPoint>
#include <cmath>

#include "interface/common/coordinates_type.h"


namespace pos_functions {


using Point = render::Point;

int poidis(Point point1, Point point2);



float poidir(Point inPoint1, Point inPoint2);

}
