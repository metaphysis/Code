// Robot Crash
// UVa ID: 204
// Verdict: Wrong Answer
// Submission Date: 2016-04-24
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double PI = 2.0 * acos(0.0), EPSILON = 1E-7;

struct robot
{
    double x, y, angle, speed;
};

struct point
{
    double x, y;
};

struct line
{
    // 使用一般形式 ax + by + c = 0 来表示直线。
    double a, b, c;
};

struct segment
{
    point start, end;
    double length;
    line l;
};

robot leftRobot, rightRobot;
int cases = 0;

vector < segment > leftSegments, rightSegments;

// 判断两条直线是否平行。
bool isParallelLine(line line1, line line2)
{
    return (fabs(line1.a - line2.a) < EPSILON) && (fabs(line1.b - line2.b) < EPSILON);
}

// 判断两条直线是否为同一条直线。
bool isSameLine(line line1, line line2)
{
    return isParallelLine(line1, line2) && (fabs(line1.c - line2.c) < EPSILON);
}

// 求两条直线的交点，如果存在交点则返回 true，否则返回 false。
point intersectionPoint(line line1, line line2)
{
    point p;

    // 两条直线相交，求出交点。
    p.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        p.y = -(line1.a * p.x + line1.c) / line1.b;
    else
        p.y = -(line2.a * p.x + line2.c) / line2.b;

    return p;
}

// 将使用斜率与直线上一点的表示方式转换为标准形式。
line pointAndSlopeToLine(point p, double slope)
{
    line lr;

    // 直线与 X 轴不垂直，系数 b 规定为 1。
    lr.a = -slope;
    lr.b = 1.0;
    lr.c = -(lr.a * p.x + lr.b * p.y);

    return lr;
}

// 包围盒测试。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

double distances(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void getSegments()
{
    leftSegments.clear();
    double slope = tan((leftRobot.angle) * PI / 180.0);
    double x = leftRobot.x, y = leftRobot.y;
    
    if (fabs(leftRobot.angle) < EPSILON)
    {
        // angle is 0
        point start = (point){x, y};
        line l = pointAndSlopeToLine(start, slope);
        point end = (point){rightRobot.x, leftRobot.y};
        double length = fabs(rightRobot.x - leftRobot.x);
        segment s = (segment){start, end, length, l};
        leftSegments.push_back(s);
    }
    else
    {
        if (leftRobot.angle > 0.0)
        {
            if (fabs(y - 10.0) > EPSILON)
            {
                point start = (point){x, y};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x + (10.0 - y) / fabs(slope), 10.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                leftSegments.push_back(s);
                x = end.x;
                y = 10.0;
                slope = -slope;
            }
        }
        else
        {
            if (fabs(y) > EPSILON)
            {
                point start = (point){x, y};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x + y / fabs(slope), 0.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                leftSegments.push_back(s);
                x = end.x;
                y = 0.0;
                slope = -slope;
            }
        }
        
        while (x < rightRobot.x)
        {
            if (slope > 0.0)
            {
                point start = (point){x, 0.0};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x + 10.0 / fabs(slope), 10.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                leftSegments.push_back(s);
                x = end.x;
                y = 10.0;
            }
            else
            {
                point start = (point){x, 10.0};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x + 10.0 / fabs(slope), 0.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                leftSegments.push_back(s);
                x = end.x;
                y = 0.0;
            }
            slope = -slope;
        }
    }
    
    rightSegments.clear();
    slope = tan((rightRobot.angle) * PI / 180.0);
    x = rightRobot.x, y = rightRobot.y;
    
    if (fabs(rightRobot.angle) == 180.0)
    {
        // angle is 180.0
        point start = (point){x, y};
        line l = pointAndSlopeToLine(start, slope);
        point end = (point){leftRobot.x, rightRobot.y};
        double length = fabs(rightRobot.x - leftRobot.x);
        segment s = (segment){start, end, length, l};
        rightSegments.push_back(s);
    }
    else
    {
        if (rightRobot.angle > 0.0)
        {
            if (fabs(y - 10.0) > EPSILON)
            {
                point start = (point){x, y};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x - (10.0 - y) / fabs(slope), 10.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                rightSegments.push_back(s);
                x = end.x;
                y = 10.0;
                slope = -slope;
            }
        }
        else
        {
            if (fabs(y) > EPSILON)
            {
                point start = (point){x, y};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x - y / fabs(slope), 0.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                rightSegments.push_back(s);
                x = end.x;
                y = 0.0;
                slope = -slope;
            }
        }
      
        while (x > leftRobot.x)
        {
            if (slope > 0.0)
            {
                point start = (point){x, 10.0};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x - 10.0 / fabs(slope), 0.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                rightSegments.push_back(s);
                x = end.x;
                y = 0.0;
            }
            else
            {
                point start = (point){x, 0.0};
                line l = pointAndSlopeToLine(start, slope);
                point end = (point){x - 10.0 / fabs(slope), 10.0};
                double length = distances(start, end);
                segment s = (segment){start, end, length, l};
                rightSegments.push_back(s);
                x = end.x;
                y = 10.0;
            }
            slope = -slope;
        }
    }
}

void collide(double x, double y)
{
    cout << "Robots collide at (";
    cout << fixed << setprecision(2) << x;
    cout << ",";
    cout << fixed << setprecision(2) << y;
    cout << ")\n\n";
}

void calculate()
{
    cases++;
    cout << "Robot Problem #" << cases << ": ";

    // special cases
    if (leftRobot.x > rightRobot.x)
    {
        cout << "Robots do not collide.\n\n";
        return;
    }

    if (leftRobot.x == rightRobot.x)
    {
        if(leftRobot.y == rightRobot.y)
            collide(leftRobot.x, leftRobot.y);
        else
            cout << "Robots do not collide.\n\n";
        return;
    }
    
    if (leftRobot.angle == 0.0 && fabs(rightRobot.angle) == 180.0)
    {
        if (fabs(leftRobot.y - rightRobot.y) < EPSILON)
        {
            double collidex = leftRobot.x + leftRobot.speed *
                (fabs(rightRobot.x - leftRobot.x) / (leftRobot.speed +
                    rightRobot.speed));
            collide(collidex, leftRobot.y);
        }
        else
            cout << "Robots do not collide.\n\n";
        return;
    }
    
    point bestPoint;
    double bestTime = 0.5;
    bool found = false;
    double leftRobotPath = 0.0;
    for (int i = 0; i < leftSegments.size(); i++)
    {
        if (i > 0)
            leftRobotPath += leftSegments[i - 1].length;
        
        double rightRobotPath = 0.0;
        for (int j = 0; j < rightSegments.size(); j++)
        {
            if (j > 0)
                rightRobotPath += rightSegments[j - 1].length;

            //cout << endl;
            //cout << leftSegments[i].start.x << " " << leftSegments[i].start.y << " ";
            //cout << leftSegments[i].end.x << " " << leftSegments[i].end.y << " ";
            //cout << leftSegments[i].l.a << " " << leftSegments[i].l.b << " " << leftSegments[i].l.c << endl;
            //cout << rightSegments[j].start.x << " " << rightSegments[j].start.y << " ";
            //cout << rightSegments[j].end.x << " " << rightSegments[j].end.y << " ";
            //cout << rightSegments[j].l.a << " " << rightSegments[j].l.b << " " << rightSegments[j].l.c << endl;
            //cout << endl;
                
            // path of left and right robot overlapped
            if (isSameLine(leftSegments[i].l, rightSegments[j].l))
            {
                double collideTime =
                    (leftRobotPath + rightRobotPath + leftSegments[i].length) /
                        (leftRobot.speed + rightRobot.speed);
                double radian = leftRobot.angle * PI / 180.0;
                double collidex = leftRobot.x + collideTime * leftRobot.speed * fabs(cos(radian));
                double collidey = collideTime * leftRobot.speed * fabs(sin(radian));
                if (radian > 0)
                {
                    collidey += leftRobot.y;
                    bool up = true;
                    while (collidey > 10.0)
                    {
                        collidey -= 10.0;
                        up = !up;
                    }
                    if (!up)
                        collidey = 10.0 - collidey;
                }
                else
                {
                    double up = false;
                    collidey += (10.0 - leftRobot.y);
                    while (collidey > 10.0)
                    {
                        collidey -= 10.0;
                        up = !up;
                    }
                    if (!up)
                        collidey = 10.0 - collidey;
                }
                collide(collidex, collidey);
                return;
            }
            
            // two lines are parallel, there is no intersection between them
            if (isParallelLine(leftSegments[i].l, rightSegments[j].l))
                continue;
                
            point p = intersectionPoint(leftSegments[i].l, rightSegments[j].l);
            if (!pointInBox(p, leftSegments[i].start, leftSegments[i].end) ||
                !pointInBox(p, rightSegments[j].start, rightSegments[j].end))
                continue;
            
            if (p.x < leftRobot.x || p.x > rightRobot.x)
                continue;
                
            double leftRobotTime = (leftRobotPath +
                    distances(p, leftSegments[i].start)) / leftRobot.speed;
            double rightRobotTime = (rightRobotPath +
                distances(p, rightSegments[i].start)) / rightRobot.speed;
            
            //cout << "intersection: " << p.x << " " << p.y << endl;
            //cout << "leftRobotTime = " << leftRobotTime << " rightRobotTime = " << rightRobotTime << endl;

            if (fabs(leftRobotTime - rightRobotTime) <= 0.5)
            {
                double minTime = min(leftRobotTime, rightRobotTime);
                if (found)
                {
                    if (fabs(minTime - bestTime) < EPSILON)
                    {
                        if (p.x < bestPoint.x)
                            bestPoint = p;
                    }
                    else if (minTime < bestTime)
                    {
                        bestTime = minTime;
                        bestPoint = p;
                    }
                }
                else
                {
                    bestPoint = p;
                    bestTime = minTime;
                    found = true;
                }
            }
        }
    }

    if (found)
        collide(bestPoint.x, bestPoint.y);
    else
        cout << "Robots do not collide.\n\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> leftRobot.x >> leftRobot.y >>
            leftRobot.angle >> leftRobot.speed;
        
        getline(cin, line);
        iss.clear();
        iss.str(line);
        iss >> rightRobot.x >> rightRobot.y >>
            rightRobot.angle >> rightRobot.speed;

        getSegments();
        
        calculate();
    }

    return 0;
}
