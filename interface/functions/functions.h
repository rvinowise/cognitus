#pragma once

#include <QPoint>
#include <cmath>

#include "interface/coordinates_type.h"

/*template<typename Point>
using Type = decltype(Point.x());
Type poidis(Point point1, Point point2) {
    return sqrt(pow(fabs(point1.x()-point2.x()),2)+pow(fabs(point1.y()-point2.y()),2));
}*/

namespace pos_functions {


using Point = render::Point;

int poidis(Point point1, Point point2) {
    return sqrt(pow(fabs(point1.x()-point2.x()),2)+pow(fabs(point1.y()-point2.y()),2));
}


}
