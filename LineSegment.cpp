#include "LineSegment.h"

int LineSegment::getX1() {
    return x1;
}

int LineSegment::getX2() {
    return x2;
}

int LineSegment::getY1() {
    return y1;
}

int LineSegment::getY2() {
    return y2;
}

LineSegment::LineSegment(int x1, int y1, int x2, int y2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

LineSegment::LineSegment(Point p1,Point p2)
{
    this->x1 = p1.x;
    this->y1 = p1.y;
    this->x2 = p2.x;
    this->y2 = p2.y;
}

coord2_t LineSegment::findSide(Point p)
/* Decides the giving point is up above or below to this line
 * return a negative value for below positive value for above
 * 0 for on the line*/
{
    coord2_t slope = 0;
    if(x2 == x1)
        return p.x - x1;
    slope =(coord2_t) (y2- y1) / (coord2_t)(x2 - x1);
    return (coord2_t)p.y - slope * p.x - y2 + slope * x2;
}

coord2_t LineSegment::findAngle()
/* returns the angle between line and +x axis in*/
{
    if(x2 == x1)
        return PI / 2;
    if(y2 == y1)
        return 0;
    coord2_t slope = (coord2_t)(y2-y1) / (coord2_t)(x2 - x1);
    if(slope<0)
        return PI - atan(abs(slope));
    else
        return atan(slope);
}

coord2_t LineSegment::lenghtSquare()
/* Returns square of length of line*/
{
    return pow(abs(y1 - y2), 2) + pow(abs(x1 - x2), 2);
}
