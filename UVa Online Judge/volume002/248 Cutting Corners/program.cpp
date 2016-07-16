// Cutting Corners
// UVa ID: 248
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct point
{
    double x, y;
};

struct segment
{
    point start, end, last;
    
    double distance()
    {
        return sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
    }
};

point findCorner(point p1, point p2, point p3)
{
    segment s1, s2, s3;
    
    s1.start = p1, s1.end = p2, s1.last = p3;
    s2.start = p1, s2.end = p3, s2.last = p2;
    s3.start = p2, s3.end = p3, s3.last = p1;

    if (s1.distance() > s2.distance() && s1.distance() > s3.distance())
    {
        p1 = s1.start, p2 = s1.end, p3 = s1.last;
    }
    else if (s2.distance() > s1.distance() && s2.distance() > s3.distance())
    {
        p1 = s1.start, p2 = s1.end, p3 = s1.last;
    }
    else if (s3.distance() > s1.distance() && s3.distance() > s2.distance())
    {
        p1 = s1.start, p2 = s1.end, p3 = s1.last;
    }
    
    point p4;
    
    // horizontal or vertical rectangle
    if (p3.y == p1.y || p3.y == p2.y)
    {
    }
    
    
    p4.x = (p2.x - p3.x) * ((p1.x - p3.x) * p2.y - (p1.y - p3.y) * p2.x) - (p1.x - p3.x) * ((p2.x - p3.x) * p1.y - (p2.y - p3.y) * p1.x);
    p4.x /= ((p2.y - p3.y) * (p1.x - p3.x) - (p1.y - p3.y) * (p2.x - p3.x));
    
    p4.y = (p2.y - p3.y) * ((p1.x - p3.x) * p2.y - (p1.y - p3.y) * p2.x) - (p1.y - p3.y) * ((p2.x - p3.x) * p1.y - (p2.y - p3.y) * p1.x);
    p4.y /= ((p2.y - p3.y) * (p1.x - p3.x) - (p1.y - p3.y) * (p2.x - p3.x));
    
    return p4;
}

int main(int argc, char *argv[])
{
	return 0;
}
