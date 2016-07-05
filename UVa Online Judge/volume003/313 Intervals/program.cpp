// Intervals
// UVa IDs: 313
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const double HALF_PI = acos(0.0);
const double EPSILON = 1E-10;

struct point
{
    double x, y;
};

struct pipe
{
    double x, y, r;
};

double distanceOfPoints(point from, point to)
{
    return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n)
    {
        point light;
        vector < pipe > pipes;

        cin >> light.x >> light.y;

        for (int i = 1; i <= n; i++)
        {
            pipe aPipe;
            cin >> aPipe.x >> aPipe.y >> aPipe.r;
            pipes.push_back(aPipe);
        }

        vector <pair<double, double>> intervals;
        for (int i = 0; i < pipes.size(); i++)
        {
            double angle1 = asin(pipes[i].r / distanceOfPoints(light, (point) { pipes[i].x, pipes[i].y }));
            double angle2 = atan2(light.y - pipes[i].y, light.x - pipes[i].x);
            double start, end;
            start = light.x - light.y / tan(angle2 - angle1);
            end = light.x - light.y / tan(angle2 + angle1);
            intervals.push_back(make_pair(start, end));
        }
        
        sort(intervals.begin(), intervals.end());

        // a bit strict on float point number epsilon
        double coverL, coverR;
        coverL = intervals[0].first;
        coverR = intervals[0].second;
        for (int i = 0; i < intervals.size(); i++)
        {
            if (intervals[i].first <= coverR)
                coverR = max(coverR, intervals[i].second);
            else
            {
                cout << fixed << setprecision(2) << coverL << " " << coverR << endl;
                coverL = intervals[i].first;
                coverR = intervals[i].second;
            }
        }
        cout << fixed << setprecision(2) << coverL<< " " << coverR << endl;
        cout << endl;
    }

    return 0;
}
