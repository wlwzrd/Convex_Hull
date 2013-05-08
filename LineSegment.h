#include "Algorithm.h"

#ifndef _LINE_SEGMENT_H_

#define PI 3.14159

class LineSegment
{
private:
    int x1;
	int y1;
	int x2;
	int y2;

public:

	int getX1();
	int getX2();
	int getY1();
	int getY2();
	LineSegment(int x1, int y1, int x2, int y2);
	LineSegment(Point p1,Point p2);
	coord2_t findSide(Point p);
	coord2_t findAngle();
	coord2_t lenghtSquare();
};

#endif
