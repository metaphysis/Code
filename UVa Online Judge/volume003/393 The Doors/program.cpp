// The Doors
// UVa ID: 393
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
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

const double EPSILON = 1E-10;

struct point
{
    double x, y;
    
    int wall;
    
    // 标记是否为有效交点
    bool is_valid;     
};

struct segment
{
    point start, end;
};

struct line
{
    // 使用一般形式 ax + by + c = 0 来表示直线。
    double a, b, c;
};

struct edge
{
    int to;
    double weight;
};

// 将两点表示的直线转换为一般形式表示。
line pointsToLine(point start, point end)
{
    line lr;

    // 判断两点 x 坐标是否相同，是表明直线为垂直 X 轴的直线，系数 a 规定为 1。
    if (fabs(start.x - end.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -start.x;
    }
    // 直线与 X 轴不垂直，系数 b 规定为 1。
    else
    {
        lr.a = -(start.y - end.y) / (start.x - end.x);
        lr.b = 1.0;
        lr.c = -lr.a * start.x - start.y;
    }

    return lr;
}

double getYAtLine(line lr, double x)
{
    return (-lr.c - lr.a * x) / lr.b;
}

// 判断两条直线是否平行。
bool isParallelLine(line line1, line line2)
{
    return (fabs(line1.a - line2.a) <= EPSILON) && (fabs(line1.b - line2.b) <= EPSILON);
}

// 判断两条直线是否为同一条直线。
bool isSameLine(line line1, line line2)
{
    return isParallelLine(line1, line2) && (fabs(line1.c - line2.c) <= EPSILON);
}

// 求两条直线的交点，如果存在交点则返回 true，否则返回 false。
point intersect(line line1, line line2)
{
    point pr;

    // 当两条直线平行时，认为其无交点。
    if (isParallelLine(line1, line2))
    {
        return (point){0.0, 0.0, false};
    }

    pr.is_valid = true;
    
    // 当两条直线重合时，任意取直线上一点作为交点。
    if (isSameLine(line1, line2))
    {
        // 系数 a 不为 0，取 y = 0。
        if (fabs(line1.a) > EPSILON)
        {
            pr.x = -line1.c / line1.a;
            pr.y = 0.0;
        }
        // 系数 b 不为 0，取 x = 0。
        else
        {
            pr.x = 0.0;
            pr.y = -line1.c / line1.b;
        }

        return pr;
    }

    // 两条直线相交，求出交点。
    pr.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        pr.y = -(line1.a * pr.x + line1.c) / line1.b;
    else
        pr.y = -(line2.a * pr.x + line2.c) / line2.b;

    return pr;
}

// 包围盒测试。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

// 判断两条线段是否相交。
bool segmentsIntersect(segment aSegment, segment bSegment)
{
    line aLine, bLine;
    point p;

    aLine = pointsToLine(aSegment.start, aSegment.end);
    bLine = pointsToLine(bSegment.start, bSegment.end);

    if (isSameLine(aLine, bLine))
        return (pointInBox(aSegment.start, bSegment.start, bSegment.end)
            || pointInBox(aSegment.end, bSegment.start, bSegment.end));

    if (isParallelLine(aLine, bLine))
        return false;

    p = intersect(aLine, bLine);
    if (p.is_valid == false)
        return false;

    return (pointInBox(p, aSegment.start, aSegment.end) &&
        pointInBox(p, bSegment.start, bSegment.end));
}

double distanceOfPoints(point &a, point &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n >= 0)
    {
        if (n == 0)
        {
            cout << "10.00" << endl;
            continue;
        }
        
        map<int, double> walls;
        map<int, vector<point>> obstacles;
        double x1, y1, y2, y3, y4;
        
        vector<point> points;
        points.push_back((point){0.0, 5.0, 0, false});
        
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> y2 >> y3 >> y4;
            walls[i] = x1;
            obstacles[i].push_back((point){0.0, y1, i, false});
            obstacles[i].push_back((point){y2, y3, i, false});
            obstacles[i].push_back((point){y4, 10.0, i, false});
            
            points.push_back((point){x1, y1, i, false});
            points.push_back((point){x1, y2, i, false});
            points.push_back((point){x1, y3, i, false});
            points.push_back((point){x1, y4, i, false});
        }
        points.push_back((point){10.0, 5.0, n + 1, false});
        
        bool go_through = true;
        for (auto obstacle : obstacles)
            for (auto aSegment : obstacle.second)
                if (aSegment.x < 5.0 && 5.0 < aSegment.y)
                {
                    go_through = false;
                    goto get_out;
                }
                
        get_out:
        if (go_through)
        {
            cout << "10.00" << endl;
            continue;
        }
    
        vector<vector<edge>> edges;
        edges.assign(points.size(), vector<edge>());
        
        for (int i = 0; i < points.size(); i++)
            for (int j = points.size() - 1; j >= 0; j--)
            {
                if (points[j].wall <= points[i].wall)
                    break;
                
                if (points[j].wall == points[i].wall + 1)
                {
                    edges[i].push_back((edge){j, distanceOfPoints(points[i], points[j])});
                    continue;
                }
                
                line lr = pointsToLine(points[i], points[j]);
                bool go_through = true; 
                for (int k = points[i].wall + 1; k <= points[j].wall - 1; k++)
                {
                    double y = getYAtLine(lr, walls[k]);
                    for (auto aSegment : obstacles[k])
                        if (aSegment.x < y && y < aSegment.y)
                        {
                            go_through = false;
                            break;
                        }
                    if (go_through == false)
                        break;
                }
                
                if (go_through)
                    edges[i].push_back((edge){j, distanceOfPoints(points[i], points[j])});
            }
            
        vector<double> distances(points.size());
        vector<bool> visited(points.size());
        fill(distances.begin(), distances.end(), 100000.0);
        
        distances[0] = 0.0;
        int current = 0;
        
        while (visited[current] == false)
        {
            visited[current] = true;
            
            for (auto element : edges[current])
                if (visited[element.to] == false && distances[current] + element.weight < distances[element.to])
                    distances[element.to] = distances[current] + element.weight;
                    
            double minDistance = 100000.0;
            for (int i = 0; i < edges.size(); i++)
                if (visited[i] == false && minDistance > distances[i])
                {
                    current = i;
                    minDistance = distances[i];
                }
        }
        
        cout << fixed << setprecision(2) << distances[points.size() - 1] << endl;
    }
    
	return 0;
}
