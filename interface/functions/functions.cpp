#include "interface/functions/functions.h"

namespace pos_functions {

int poidis(Point point1, Point point2) {
    return sqrt(pow(fabs(point1.x()-point2.x()),2)+pow(fabs(point1.y()-point2.y()),2));
}


float poidir(Point inPoint1, Point inPoint2) {
    float x1 = inPoint1.x();
    float y1 = inPoint1.y();
    float x2 = inPoint2.x();
    float y2 = inPoint2.y();
    if (x1==x2) {
        if (y1>y2) {
            return 0;
        } else {
            return 180;
        }
    } else {
        if ((x1<x2)&&(y1>y2)) {
            return int(atan((y2-y1)/(x2-x1))*180/3.14)+90;
        } else if (x1>x2) {
            return int(atan((y2-y1)/(x2-x1))*180/3.14)-90;
        } else {
            return int(atan((y2-y1)/(x2-x1))*180/3.14)-270;
        }
    }
}

}
