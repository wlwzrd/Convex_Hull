#include <iostream>
#include <vector>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Algorithm.h"

using namespace std;

// ===== ENTRY POINT =====
int main()
{
    int numPoints = 10000000;
    string algorithm = "Monotonic Chain";
    vector<Point> points;

    /* initialize random seed: */

    srand ( time(NULL) );

    for (int i = 0; i < numPoints; ++i)
    {

        int randomX = rand() % numPoints;
        int randomY = rand() % numPoints;
        Point p;
        p.x = randomX;
        p.y = randomY;
        points.push_back(p);
    }

    // Time analysis
    clock_t start;
    clock_t stop;

    cout << "Algorithm: " << algorithm << endl;
    cout << "Number of Points: " << numPoints << endl;

    vector<Point> convexHull = Algorithm::monotoneChain(points);
    /*
    cout << "===== Convex Hull Points =====" << endl;

    for (int j = 0; j < convexHull.size(); ++j)
    {
        cout << "(" << convexHull.at(j).x << ", " << convexHull.at(j).y << ")" << endl;
    }
    */
    system("pause");
    return 0;
}
