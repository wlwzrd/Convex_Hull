/*
* Class: ConvexHull
* Description: Implements three types of algorithms to solve the convex hull problem
* Author: Carlos Felipe Perea Tanaka
* Date: November 11th, 2012
*/

#ifndef _ALGORTHM_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "ConvexHull.h"
#include "GrahamScanConvexHull.h"
#include <time.h>

#define PI 3.14159

using namespace std;

typedef int coord_t;         // coordinate type
typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

// Point structure used in the graham scan algorithm
// Represents a point in space
struct Point {
        coord_t x, y;
        bool operator <(const Point &p) const {
                return x < p.x || (x == p.x && y < p.y);
        }
};

// Represents a line segment
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

class Algorithm
{

public:

    static vector<Point> bruteForce(vector<Point> points);
    static vector<Point> grahamScan(vector<Point> points);
    static vector<Point> monotoneChain(vector<Point> points);

private:

    static coord2_t cross(const Point &O, const Point &A, const Point &B);
    static coord2_t dp(Point pt1, Point pt2);

};

#endif
