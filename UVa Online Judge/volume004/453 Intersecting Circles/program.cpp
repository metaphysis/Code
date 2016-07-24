// Intersecting Circles
// UVa ID: 453
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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const double epsilon = 1e-6, epsilon2 = 5.14e-5;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cout.precision(3);

    double x1, y1, r1, x2, y2, r2;

    while (cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2)
    {
        if (r2 > r1)
            swap(x1, x2), swap(y1, y2), swap(r1, r2);

        double distance1 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double distance2 = r1 + r2;

        // same circle
        if (distance1 <= epsilon)
        {
            if (fabs(r1 - r2) <= epsilon)
            {
                if (r1 > epsilon)
                    cout << "THE CIRCLES ARE THE SAME\n";
                else
                    cout << '(' << fixed << x1 + epsilon2 << ',' << fixed << y1 + epsilon2 << ")\n";
            }
            else
                cout << "NO INTERSECTION\n";
            continue;
        }

        // no intersection, one circle contains within another circle
        if (distance1 > distance2 + epsilon || distance1 + r2 + epsilon < r1)
        {
            cout << "NO INTERSECTION\n";
            continue;
        }

        // one intersecion
        if (fabs(distance1 - distance2) <= epsilon)
        {
            x1 += r1 / (r1 + r2) * (x2 - x1);
            y1 += r1 / (r1 + r2) * (y2 - y1);
            cout << '(' << fixed << x1 + epsilon2 << ',' << fixed << y1 + epsilon2 << ")\n";
            continue;
        }

        if (fabs(distance1 + r2 - r1) <= epsilon)
        {
            x1 += distance1 / r1 * (x2 - x1);
            y1 += distance1 / r1 * (y2 - y1);
            cout << '(' << fixed << x1 + epsilon2 << ',' << fixed << y1 + epsilon2 << ")\n";
            continue;
        }

        // two intersection
        double a, h;
        a = (r1 * r1 - r2 * r2 + distance1 * distance1) / (2 * distance1);
        h = sqrt(r1 * r1 - a * a);
        double x3 = (x2 - x1) * (a / distance1) + x1, y3 = (y2 - y1) * (a / distance1) + y1;
        
        double x4, y4, x5, y5;
        x4 = x3 + h * (y2 - y1) / distance1;
        y4 = y3 - h * (x2 - x1) / distance1;
        x5 = x3 - h * (y2 - y1) / distance1;
        y5 = y3 + h * (x2 - x1) / distance1;

        if (fabs(x4 - x5) <= epsilon && y4 > y5) swap(y4, y5);
        else if (x4 > x5) swap(x4, x5), swap(y4, y5);
        
        cout << '(' << fixed << x4 << ',' << fixed << y4 << ")(";
        cout << fixed << x5 << ',' << fixed << y5 << ")\n";
    }

    return 0;
}
