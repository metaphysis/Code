// A Hole to Catch a Man
// UVa ID: 10060
// Verdict: Accepted
// Submission Date: 2018-02-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

const double PI = 2 * acos(0.0);

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

vector<point> pg;

double getArea()
{
    double area = 0.0;
    if (pg.size() <= 2) return area;
    for (int i = 0; i < pg.size() - 1; i++)
        area += (pg[i].x * pg[i + 1].y - pg[i].y * pg[i + 1].x);
    return fabs(area) / 2;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string line;
    double Ti, Xi, Yi, R, T, volumeSteel, volumeCover;

    while (cin >> n, n > 0)
    {
        cin.ignore(1024, '\n');

        volumeSteel = 0;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            iss >> Ti;
    
            pg.clear();
            while (iss >> Xi >> Yi) pg.push_back(point(Xi, Yi));

            volumeSteel += getArea() * Ti;
        }
        
        cin >> R >> T;
        volumeCover = PI * R * R * T;
        
        cout << (int)(volumeSteel / volumeCover) << '\n';
    }

    return 0;
}
