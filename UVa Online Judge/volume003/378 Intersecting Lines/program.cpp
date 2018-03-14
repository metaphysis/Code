// Intersecting Lines
// UVa ID: 378
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-10;

struct point
{
    double x, y;
    
    // 标记是否为有效交点
    bool is_valid;     
};

struct line
{
    // 使用一般形式 ax + by + c = 0 来表示直线。
    double a, b, c;
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

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        cout << "INTERSECTING LINES OUTPUT" << endl;
        
        double x1, y1, x2, y2, x3, y3, x4, y4;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
            
            point a = (point){x1, y1};
            point b = (point){x2, y2};
            point c = (point){x3, y3};
            point d = (point){x4, y4};
            
            line line1 = pointsToLine(a, b);
            line line2 = pointsToLine(c, d);
            
            if (isSameLine(line1, line2)) cout << "LINE" << endl;
            else if (isParallelLine(line1, line2)) cout << "NONE" << endl;
            else
            {
                point pi = intersect(line1, line2);
                cout << "POINT " << fixed << setprecision(2) << pi.x;
                cout << " " << fixed << setprecision(2) << pi.y << endl;
            }
        }
        
        cout << "END OF OUTPUT" << endl;
    }
    
	return 0;
}
