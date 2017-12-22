// Campus Roads
// UVa ID: 11473
// Verdict: Accepted
// Submission Date: 2017-12-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n, t;
        cin >> n >> t;
        
        double xi, yi;
        polygon pg;
        
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi;
            pg.push_back(point(xi, yi));
        }
        
        double length = 0.0;
        for (int i = 1; i < n; i++)
            length += abs(pg[i] - pg[i - 1]);
        
        cout << "Road #" << c << ":\n";
        double gap = length / (t - 1);

        cout << fixed << setprecision(2) << pg.front().x << ' ' << pg.front().y << '\n';
 
        double walked = 0.0;
        point tree = pg.front();

        int k = 1;
        while (k < n)
        {
            double dist = abs(tree - pg[k]);
            if (walked + dist > gap + 1e-7)
            {
                double scala = gap - walked;
                tree = tree + (pg[k] - tree) * scala / dist;
                cout << fixed << setprecision(2) << tree.x << ' ' << tree.y << '\n';
                walked = 0.0;
            }
            else
            {
                tree = pg[k];
                walked += dist;
                k++;
            }
        }
        
        cout << fixed << setprecision(2) << pg.back().x << ' ' << pg.back().y << '\n';
        cout << '\n';
    }

    return 0;
}
