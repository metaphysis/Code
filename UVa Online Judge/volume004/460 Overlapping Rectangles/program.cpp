// Overlapping Rectangles
// UVa ID: 460
// Verdict: Accepted
// Submission Date: 2016-07-17
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct point
{
    int x, y;
};

struct rectangle
{
    point left_bottom, left_top, right_top, right_bottom;
};

struct line
{
    point start, end;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    int x1, y1, x2, y2;
    for (int i = 1; i <= cases; i++)
    {
        if (i > 1) cout << endl;
        
        cin >> x1 >> y1 >> x2 >> y2;
        rectangle rect1;
        rect1.left_bottom = (point){x1, y1};
        rect1.left_top = (point){x1, y2};
        rect1.right_top = (point){x2, y2};
        rect1.right_bottom = (point){x2, y1};
        
        cin >> x1 >> y1 >> x2 >> y2;
        rectangle rect2;
        rect2.left_bottom = (point){x1, y1};
        rect2.left_top = (point){x1, y2};
        rect2.right_top = (point){x2, y2};
        rect2.right_bottom = (point){x2, y1};
        
        // half plane intersection
        line bottom_edge, right_edge, top_edge, left_edge;
        
        bottom_edge.start = rect2.left_bottom;
        bottom_edge.end = rect2.right_bottom;
        if (rect1.left_bottom.y >= rect2.left_bottom.y)
        {
            bottom_edge.start = rect1.left_bottom;
            bottom_edge.end = rect1.right_bottom;
        }
        
        right_edge.start = rect2.right_bottom;
        right_edge.end = rect2.right_top;
        if (rect1.right_bottom.x <= rect2.right_bottom.x)
        {
            right_edge.start = rect1.right_bottom;
            right_edge.end = rect1.right_top;
        }
        
        top_edge.start = rect2.right_top;
        top_edge.end = rect2.left_top;
        if (rect1.right_top.y <= rect2.right_top.y)
        {
            top_edge.start = rect1.right_top;
            top_edge.end = rect1.left_top;
        }
        
        left_edge.start = rect2.left_top;
        left_edge.end = rect2.left_bottom;
        if (rect1.left_top.x >= rect2.left_top.x)
        {
            left_edge.start = rect1.left_top;
            left_edge.end = rect1.left_bottom;
        }

        point intersect1, intersect2, intersect3, intersect4;
        if (left_edge.start.x < bottom_edge.start.x || left_edge.start.x > bottom_edge.end.x ||
            bottom_edge.start.y < left_edge.end.y || bottom_edge.start.y > left_edge.start.y)
        {
            cout << "No Overlap\n";
            continue;
        }
        intersect1.x = left_edge.start.x, intersect1.y = bottom_edge.start.y;
        
        if (right_edge.start.x < bottom_edge.start.x || right_edge.start.x > bottom_edge.end.x ||
            bottom_edge.start.y < right_edge.start.y || bottom_edge.start.y > right_edge.end.y)
        {
            cout << "No Overlap\n";
            continue;
        }
        intersect2.x = right_edge.start.x, intersect2.y = bottom_edge.start.y;
        
        if (right_edge.start.x < top_edge.end.x || right_edge.start.x > top_edge.start.x ||
            top_edge.start.y < right_edge.start.y || top_edge.start.y > right_edge.end.y)
        {
            cout << "No Overlap\n";
            continue;
        }
        intersect3.x = right_edge.start.x, intersect3.y = top_edge.start.y;
        
        if (left_edge.start.x < top_edge.end.x || left_edge.start.x > top_edge.start.x ||
            top_edge.start.y < left_edge.end.y || top_edge.start.y > left_edge.start.y)
        {
            cout << "No Overlap\n";
            continue;
        }
        intersect4.x = left_edge.start.x, intersect4.y = top_edge.start.y;
        
        // calculate the area of rectangle, if area bigger than 0, overlapped
        int area = intersect1.x * intersect2.y - intersect2.x * intersect1.y;
        area += intersect2.x * intersect3.y - intersect3.x * intersect2.y;
        area += intersect3.x * intersect4.y - intersect4.x * intersect3.y;
        area += intersect4.x * intersect1.y - intersect1.x * intersect4.y;
        
        if (area == 0)
        {
            cout << "No Overlap\n";
            continue;
        }
        
        cout << intersect1.x << ' ' << intersect1.y << ' ' << intersect3.x << ' ' << intersect3.y << '\n';
    }
    
	return 0;
}
