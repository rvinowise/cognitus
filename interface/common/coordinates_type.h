#pragma once

#include <QtCore>
#include <QColor>
#include <QVector2D>

namespace render {

//using Point = QVector2D;
class Point: public QVector2D
{
public:
    Point():QVector2D{}{}
    Point(const QPoint& point):QVector2D{point}{}
    Point(const QPointF& point):QVector2D{point}{}
    Point(float x, float y):QVector2D{x,y}{}
    Point(const QVector2D& other):QVector2D{other}{}
    /*Point& operator+(const Point& a, const Point& b){
        return Point(a.x() );
        //return *this;
    }*/
    Point operator+(const Point &other) {
        return Point(this->x()+other.x(), this->y()+ other.y());
    }

    Point operator-(const Point &other) {
        return Point(this->x()-other.x(), this->y()- other.y());
    }


};



using Rect = QRectF;
using Color = QColor;



}
