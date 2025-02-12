#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point2D
{
    double x, y;
    Point2D() {x = 0.0; y = 0.0;}
    Point2D(double _x, double _y) {x = _x; y = _y;}

    bool operator == (const Point2D &p) const {
        return (x == p.x) && (y == p.y);
    }
};
#endif