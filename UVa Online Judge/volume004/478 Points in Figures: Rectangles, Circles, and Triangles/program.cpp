// Points in Figures: Rectangles, Circles, and Triangles
// UVa ID: 478
// Verdict: Accepted
// Submission Date: 2016-07-16
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

struct figure
{
    char type;
    point left_top, right_top, right_bottom, left_bottom;
    point center;
    double radius;
};

vector<figure> figures;
int cases = 0;

double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

void is_contained(point test)
{
    ++cases;
    bool flag = false;
    for (int i = 0; i < figures.size(); i++)
    {
        if (figures[i].type == 'r')
        {
            figure rect = figures[i];
            if (direction(rect.left_top, rect.right_top, test) > EPSILON &&
                direction(rect.right_top, rect.right_bottom, test) > EPSILON &&
                direction(rect.right_bottom, rect.left_bottom, test) > EPSILON &&
                direction(rect.left_bottom, rect.left_top, test) > EPSILON)
            {
                flag = true;
                cout << "Point " << cases << " is contained in figure " << (i + 1) << '\n';
            }
        }
        else if (figures[i].type == 't')
        {
            figure triangle = figures[i];
            if ((direction(triangle.left_top, triangle.right_top, test) > EPSILON &&
                direction(triangle.right_top, triangle.right_bottom, test) > EPSILON &&
                direction(triangle.right_bottom, triangle.left_top, test) > EPSILON) ||
                (direction(triangle.left_top, triangle.right_top, test) < -EPSILON &&
                direction(triangle.right_top, triangle.right_bottom, test) < -EPSILON &&
                direction(triangle.right_bottom, triangle.left_top, test) < -EPSILON))
            {
                flag = true;
                cout << "Point " << cases << " is contained in figure " << (i + 1) << '\n';
            }
        }
        else
        {
            figure circle = figures[i];
            double rr = pow(test.x - circle.center.x, 2) + pow(test.y - circle.center.y, 2);
            if (rr < pow(circle.radius, 2) - EPSILON)
            {
                flag = true;
                cout << "Point " << cases << " is contained in figure " << (i + 1) << '\n';
            }
        }
    }
    
    if (!flag) cout << "Point " << cases << " is not contained in any figure" << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char input;
    while (cin >> input, input != '*')
    {
        if (input == 'r')
        {
            double left_top_x, left_top_y, right_bottom_x, right_bottom_y;
            cin >> left_top_x >> left_top_y >> right_bottom_x >> right_bottom_y;
            
            figure rect;
            rect.type = 'r';
            rect.left_top = (point){left_top_x, left_top_y};
            rect.right_top = (point){right_bottom_x, left_top_y};
            rect.right_bottom = (point){right_bottom_x, right_bottom_y};
            rect.left_bottom = (point){left_top_x, right_bottom_y};
            
            figures.push_back(rect);
        }
        else if (input == 't')
        {
            figure triangle;
            triangle.type = 't';
            
            double x, y;
            cin >> x >> y;
            triangle.left_top = (point){x, y};
            cin >> x >> y;
            triangle.right_top = (point){x, y};
            cin >> x >> y;
            triangle.right_bottom = (point){x, y};
            
            figures.push_back(triangle);
        }
        else
        {
            double center_x, center_y, radius;
            cin >> center_x >> center_y >> radius;
            
            figure circle;
            circle.type = 'c';
            circle.center = (point){center_x, center_y};
            circle.radius = radius;
            
            figures.push_back(circle);
        }
    }
    
    string test_x, test_y;
    while (cin >> test_x >> test_y)
    {
        if (test_x == "9999.9" && test_y == "9999.9") break;
        is_contained((point){stod(test_x), stod(test_y)});
    }
    
	return 0;
}
