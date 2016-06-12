// Monitoring Wheelchair Patients
// UVa IDs: 237
// Verdict: Wrong Answer
// Submission Date: 2016-06-07
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

const double PI = 2.0 * acos(0.0), EPSILON = numeric_limits<float>::epsilon();

struct point
{
    double x, y;
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

    // 当两条直线平行或重合时，认为其无交点。
    if (isParallelLine(line1, line2) || isSameLine(line1, line2))
        return (point){0.0, 0.0, false};

    // 两条直线相交，求出交点。
    pr.is_valid = true;
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

int main(int argc, char *argv[])
{
    point left_top = (point){0.0, 200.0};
    point right_top = (point){400.0, 200.0};
    point left_bottom = (point){0.0, 0.0};
    point right_bottom = (point){400.0, 0.0};
    
    line left_line = pointsToLine(left_bottom, left_top);
    line top_line = pointsToLine(left_top, right_top);
    line right_line = pointsToLine(right_top, right_bottom);
    line bottom_line = pointsToLine(right_bottom, left_bottom);
    
    int lines, cases = 0;
    
    while (cin >> lines, lines > 0)
    {
        double startx = 200.0, starty = 0.0, endx = 200.0, endy = 0.0;
        double total_distance = 0.0, maximum_distance = 0.0;
        double first_out_x, first_out_y, first_out_time;
        bool first_out_found = false;
        
        double t1, t2, speed, bearing, old_bearing;
        for (int i = 1; i <= lines; i++)
        {
            cin >> t1 >> t2 >> speed >> bearing;
            
            double distance_moved = speed * (t2 - t1);
            total_distance += distance_moved;
            
            old_bearing = bearing;
            bearing = (bearing / 180.0) * PI;
            
            startx = endx;
            starty = endy;
            endx += distance_moved * sin(bearing);
            endy += distance_moved * cos(bearing);
            
            double distance_from_start = sqrt(pow(endx - 200.0, 2) + pow(endy, 2));
            
            if (distance_from_start > maximum_distance + EPSILON)
                maximum_distance = distance_from_start;
            
            if (first_out_found == false)
            {
                if (endx + EPSILON < 0.0 || endx > 400.0 + EPSILON || endy + EPSILON < 0.0 || endy > 200.0 + EPSILON)
                {
                    line traveled = pointsToLine((point){startx, starty}, (point){endx, endy});
                    line boundary[4] = {left_line, top_line, right_line, bottom_line};
                    point endpoint[4] = {left_bottom, left_top, right_top, right_bottom};
                    
                    int counter = 0;
                    for (int k = 0; k < 4; k++)
                    {
                        // 判断是否重合，如果重合而且超出限制区域，使用以上求交点的方法无法求出离开限制区域时的坐标
                        point intersection;
                        if (isSameLine(traveled, boundary[k]))
                        {
                            // 上边界
                            if (fabs(endy - 200.0) <= EPSILON)
                            {
                                if (right_top.x < max(startx, endx))
                                    intersection = right_top;
                                else if (left_top.x > min(startx, endx))
                                    intersection = left_top;
                                else
                                    continue;
                            }
                            // 下边界
                            else if (fabs(endy) <= EPSILON)
                            {
                                if (right_bottom.x < max(startx, endx))
                                    intersection = right_bottom;
                                else if (left_bottom.x > min(startx, endx))
                                    intersection = left_bottom;
                                else
                                    continue;
                            }
                            // 右边界
                            else if (fabs(endx - 400.0) <= EPSILON)
                            {
                                if (right_top.y < max(starty, endy))
                                    intersection = right_top;
                                else if (right_bottom.y > min(starty, endy))
                                    intersection = right_bottom;
                                else
                                    continue;
                            }
                            // 左边界
                            else if (fabs(endx) <= EPSILON)
                            {
                                if (left_top.y < max(starty, endy))
                                    intersection = left_top;
                                else if (left_bottom.y  > min(starty, endy))
                                    intersection = left_bottom;
                                else
                                    continue;
                            }

                            counter++;
                        }
                        else
                        {
                            intersection = intersect(traveled, boundary[k]);
                            if (intersection.is_valid == false)
                                continue;
                            
                            if (!pointInBox(intersection, (point){startx, starty}, (point){endx, endy}) ||
                                !pointInBox(intersection, endpoint[k], endpoint[(k + 1) % 4]))
                                continue;
                                
                            counter++;
                        }

                        assert(counter > 0);

                        double distance_moved = sqrt(pow(intersection.x - startx, 2) + pow(intersection.y - starty, 2));
                        first_out_x = intersection.x;
                        first_out_y = intersection.y;
                        first_out_time = t1 + (distance_moved) / speed;
                        first_out_found = true;
                        break;
                    }
                }
            }
        }

        cout << "Case Number " << ++cases << endl;
        if (first_out_found)
        {
            cout << "Left restricted area at point (";
            cout << fixed << setprecision(1) << (first_out_x + EPSILON);
            cout << fixed << setprecision(1) << "," << (first_out_y + EPSILON);
            cout << ") and time ";
            cout << fixed << setprecision(1) << (first_out_time + EPSILON);
            cout << " sec." << endl;
        }
        else
        {
            cout << "No departure from restricted area" << endl;
            cout << "Maximum distance patient traveled from door was ";
            cout << fixed << setprecision(1) << (maximum_distance + EPSILON) << " feet" << endl;
        }
        cout << "Total distance traveled was ";
        cout << fixed << setprecision(1) << (total_distance + EPSILON) << " feet" << endl;
        cout << "***************************************" << endl;
    }
    
	return 0;
}
