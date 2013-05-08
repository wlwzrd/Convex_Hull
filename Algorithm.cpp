#include "Algorithm.h"

// Line segment

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

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t Algorithm::cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Dot product devided by the norm to have the cos because sorting the angle is the same as sorting the cos in [0, Pi].
coord2_t Algorithm::dp(Point pt1, Point pt2)
{
    return (pt2.x-pt1.x)/sqrt((pt2.x-pt1.x)*(pt2.x-pt1.x) + (pt2.y-pt1.y)*(pt2.y-pt1.y));
}

// Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Asymptotic complexity: O(n log n).
// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> Algorithm::monotoneChain(vector<Point> points)
{
    // Time analysis
    clock_t start;
    clock_t stop;

    start = clock();

    int n = points.size();
    int k = 0;
    vector<Point> H(2*n);

    // Sort points lexicographically
    sort(points.begin(), points.end());

    // Build lower hull
    for (int i = 0; i < n; i++) {
            while (k >= 2 && cross(H[k-2], H[k-1], points[i]) <= 0) k--;
            H[k++] = points[i];
    }

    // Build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
            while (k >= t && cross(H[k-2], H[k-1], points[i]) <= 0) k--;
            H[k++] = points[i];
    }

    H.resize(k);

    stop = clock();

    double time = (double)(stop - start) / CLOCKS_PER_SEC;

    cout << "Monotone Chain Running Time: " << time << " s" << endl << endl;

    return H;
}

// Implementation of Graham scan 2D convex hull algorithm.
// Asymptotic complexity: O(n log n).
vector<Point> Algorithm::grahamScan(vector<Point> points)
{
    vector<point2d> points2d;
    vector<point2d> convex_hull;
    vector<Point> result;

    // Convert all the points of type Point to type point2d
    for (int i = 0; i < points.size(); ++i)
    {
        point2d point(points.at(i).x, points.at(i).y);
        points2d.push_back(point);
    }

    // Time analysis
    clock_t start;
    clock_t stop;

    start = clock();

    // execute the algorithm
    GrahamScanConvexHull()(points2d, convex_hull);

    stop = clock();

    double time = (double)(stop - start) / CLOCKS_PER_SEC;

    cout << "Graham Scan Running Time: " << time << " s" << endl << endl;

    // Convert all the points of type point2d to Point
    for (int j = 0; j < convex_hull.size(); ++j)
    {
        Point p;
        p.x = convex_hull.at(j).x;
        p.y = convex_hull.at(j).y;
        result.push_back(p);
    }

    return result;
}

// Implementation of Brute Force 2D convex hull algorithm.
// Asymptotic complexity: O(n^3).
vector<Point> Algorithm::bruteForce(vector<Point> points)
{
    // Time analysis
    clock_t start;
    clock_t stop;

    start = clock();

    bool alt=false,ust=false;
    vector<Point> corner;
    for(int i=0;i<points.size();i++)
    {
        for(int j=i+1;j<points.size();j++)
        {
            LineSegment a(points.at(i),points.at(j));
            // draws a line for all double combination of points
            for(int k=0;k<points.size();k++)
            {
                if(k==i || k==j)
                    continue;
                //compares if all other point are below or above line
                coord2_t result=a.findSide(points.at(k));
                if(result<0)
                {
                    alt=true;
                }
                else if(result>0)
                {
                    ust=true;
                }

                // if result equals to 0 point is on the line ignore this point
            }
            if(alt && ust)
            {
                alt=false; ust=false;
            }
            else
            {
                corner.push_back(points.at(i)); // add points
                corner.push_back(points.at(j));
            }
            alt=false; ust=false;
        }
    }

    stop = clock();

    double time = (double)(stop - start) / CLOCKS_PER_SEC;

    cout << "Brute Force Running Time: " << time << " s" << endl << endl;

    // Remove duplicate points
    for (int ii = corner.size() - 1; ii > 0; ii--)
    {
        Point p1 = corner.at(ii);
        for (int jj = 0; jj < corner.size(); jj++)
        {
            if (ii == jj)
                continue;
            Point p2 = corner.at(jj);
            if (p1.x == p2.x && p1.y == p2.y)
            {
                corner.erase(corner.begin()+jj);
                break;
            }
        }
    }

    return corner;
}
