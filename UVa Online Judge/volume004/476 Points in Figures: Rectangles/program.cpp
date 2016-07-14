// Points in Figures: Rectangles
// UVa IDs: 476
// Verdict: Accepted
// Submission Date: 2016-07-14
// UVa Run Time: 0.010s
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

const double EPSILON = 1e-7;

struct point
{
    double x, y;
};

struct rectangle
{
    point left_top, right_top, right_bottom, left_bottom;
};

vector<rectangle> rectangles;
int cases = 0;

double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

void is_contained(point test)
{
    ++cases;
    bool flag = false;
    for (int i = 0; i < rectangles.size(); i++)
    {
        rectangle rect = rectangles[i];
        if (direction(rect.left_top, rect.right_top, test) > EPSILON &&
            direction(rect.right_top, rect.right_bottom, test) > EPSILON &&
            direction(rect.right_bottom, rect.left_bottom, test) > EPSILON &&
            direction(rect.left_bottom, rect.left_top, test) > EPSILON)
        {
            flag = true;
            cout << "Point " << cases << " is contained in figure " << (i + 1) << endl;
        }
    }
    
    if (!flag) cout << "Point " << cases << " is not contained in any figure" << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    char input;
    while (cin >> input, input != '*')
    {
        double left_top_x, left_top_y, right_bottom_x, right_bottom_y;
        cin >> left_top_x >> left_top_y >> right_bottom_x >> right_bottom_y;
        rectangle rect;
        rect.left_top = (point){left_top_x, left_top_y};
        rect.right_top = (point){right_bottom_x, left_top_y};
        rect.right_bottom = (point){right_bottom_x, right_bottom_y};
        rect.left_bottom = (point){left_top_x, right_bottom_y};
        rectangles.push_back(rect);
    }
    
    string test_x, test_y;
    while (cin >> test_x >> test_y)
    {
        if (test_x == "9999.9" && test_y == "9999.9") break;
        is_contained((point){stod(test_x), stod(test_y)});
    }
    
	return 0;
}
