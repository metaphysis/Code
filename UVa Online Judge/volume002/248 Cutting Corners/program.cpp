// Cutting Corners
// UVa ID: 248
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.040s
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

const double MAX_DISTANCE = 1000000.0, EPSILON = 1e-6;

struct point
{
    double x, y;
};

struct segment
{
    point start, end;
};

struct rectangle
{
    point top_left, top_right, bottom_left, bottom_right;
};

struct edge
{
    int label;
    double dist;
};

point starting, stopping;
vector<point> allPoints;
vector<rectangle> allRectangles;

vector<vector<edge>> edges;
vector<double> distances;
vector<bool> visited;

double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

double distanceOfPoints(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void getPointAndRectangle(point p1, point p2, point p3)
{
    if (distanceOfPoints(p1, p2) + EPSILON < distanceOfPoints(p2, p3))
        getPointAndRectangle(p2, p3, p1);
    else if (distanceOfPoints(p1, p2) + EPSILON < distanceOfPoints(p1, p3))
        getPointAndRectangle(p1, p3, p2);
    else
    {
        point p4 = (point){p1.x - (p3.x - p2.x), p1.y - (p3.y - p2.y)};
        
        allPoints.push_back(p1);
        allPoints.push_back(p2);
        allPoints.push_back(p3);
        allPoints.push_back(p4);
            
        if (direction(p1, p2, p3) > EPSILON) 
            allRectangles.push_back((rectangle){p1, p3, p2, p4});
        else
            allRectangles.push_back((rectangle){p1, p4, p2, p3});
    }
}

bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    return ((d1 * d2 < 0) && (d3 * d4) < 0);
}

bool pointInRectangle(point p, rectangle r)
{
    double d1 = direction(r.top_left, r.bottom_left, p);
    double d2 = direction(r.bottom_left, r.bottom_right, p);
    double d3 = direction(r.bottom_right, r.top_right, p);
    double d4 = direction(r.top_right, r.top_left, p);
    
    return (d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0);
}

bool intersected(segment s)
{
    for (int i = 0; i < allRectangles.size(); i++)
    {
        rectangle r = allRectangles[i];

        double d1 = direction(s.start, s.end, r.top_left);
        double d2 = direction(s.start, s.end, r.top_right);
        double d3 = direction(s.start, s.end, r.bottom_left);
        double d4 = direction(s.start, s.end, r.bottom_right);

        if ((d1 >= -EPSILON && d2 >= -EPSILON && d3 >= -EPSILON && d4 >= -EPSILON) ||
            (d1 <= EPSILON && d2 <= EPSILON && d3 <= EPSILON && d4 <= EPSILON))
            continue;
        else
        {
            if (pointInRectangle(s.start, r) || pointInRectangle(s.end, r))
                return true;

            if (segmentsIntersect(s, (segment){r.top_left, r.bottom_left}) ||
                segmentsIntersect(s, (segment){r.bottom_left, r.bottom_right}) ||
                segmentsIntersect(s, (segment){r.bottom_right, r.top_right}) ||
                segmentsIntersect(s, (segment){r.top_right, r.top_left}))
                return true;
        }
    }
    
    return false;
}

void prepare()
{
    edges.clear();
    edges.resize(allPoints.size(), vector<edge>());
    for (int i = 0; i < allPoints.size(); i++)
        for (int j = i + 1; j < allPoints.size(); j++)
        {
            segment s = (segment){allPoints[i], allPoints[j]};
            if (!intersected(s))
            {
                edges[i].push_back((edge){j, distanceOfPoints(s.start, s.end)});
                edges[j].push_back((edge){i, distanceOfPoints(s.start, s.end)});
            }
        }
}

void mooreDijkstra(int start)
{
    visited.clear();
    distances.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        visited.push_back(false);
        distances.push_back(MAX_DISTANCE);
    }

    distances[start] = 0.0;
    while (!visited[start])
    {
        visited[start] = true;
        for (int i = 0; i < edges[start].size(); i++)
        {
            edge e = edges[start][i];
            if (!visited[e.label] && distances[start] + e.dist + EPSILON < distances[e.label])
                distances[e.label] = distances[start] + e.dist;
        }

        double minDistance = MAX_DISTANCE;
        for (int i = 0; i < edges.size(); i++)
            if (!visited[i] && minDistance > distances[i] + EPSILON)
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    int n, cases = 0;

    while (cin >> n, n >= 0)
    {
        allPoints.clear();
        allRectangles.clear();

        cin >> starting.x >> starting.y >> stopping.x >> stopping.y;
        
        allPoints.push_back(starting);
        allPoints.push_back(stopping);
        
        point p1, p2, p3;
        for (int i = 1; i <= n; i++)
        {
            cin >> p1.x >> p1.y;
            cin >> p2.x >> p2.y;
            cin >> p3.x >> p3.y;
            
            getPointAndRectangle(p1, p2, p3);
        }
        
        prepare();
        mooreDijkstra(0);
        
        if (cases > 0) cout << '\n';
        cout << "Scenario #" << ++cases << '\n';
        cout << "   route distance: ";
        cout << fixed << setprecision(2) << distances[1] << '\n';
    }
    
	return 0;
}
