// Pendulum
// UVa ID: 319
// Verdict: Accepted
// Submission Date: 2017-05-29
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
#include <vector>

using namespace std;

const double EPSILON = 1e-7, PI = 2.0 * acos(0.0);

struct point
{
    double x, y;
};

double getDist(const point & p1, const point & p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double cp(const point &a, const point &b, const point &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    double x1, y1, lengthOfString;

    while (cin >> n >> lengthOfString, lengthOfString > 0.0)
    {
        cout << "Pendulum #" << ++cases << '\n';

        vector<point> hooks;
        hooks.push_back(point{0.0, 0.0});

        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1;

            if (y1 > 0) continue;
            if (lengthOfString + EPSILON < sqrt(x1 * x1 + y1 * y1)) continue;

            hooks.push_back(point{x1, y1});
        }

        int lastHookIdx = 0, nextHookIdx;
        double lastTheta = -PI, nextTheta, rightmostAngle;
        double orbit = 0.0;

        while (true)
        {
            nextHookIdx = -1;
            rightmostAngle = asin(fabs(hooks[lastHookIdx].y) / lengthOfString);

            for (int i = 0; i < hooks.size(); i++)
            {
                if (i == lastHookIdx) continue;

                double currentDist = getDist(hooks[i], hooks[lastHookIdx]);
                if (lengthOfString + EPSILON < currentDist) continue;

                double theta =
                    atan2(hooks[i].y - hooks[lastHookIdx].y, hooks[i].x - hooks[lastHookIdx].x);
                if (theta - rightmostAngle > EPSILON || theta + EPSILON < lastTheta)
                {
                    if (fabs(hooks[lastHookIdx].y) < lengthOfString + EPSILON) continue;
                }

                if (nextHookIdx == -1)
                {
                    nextTheta = theta;
                    nextHookIdx = i;
                }
                else
                {
                    double CP = cp(hooks[lastHookIdx], hooks[nextHookIdx], hooks[i]);
                    if (fabs(CP) < EPSILON)
                    {
                        double lastDist = getDist(hooks[nextHookIdx], hooks[lastHookIdx]);
                        if (lastDist + EPSILON < currentDist)
                        {
                            nextTheta = theta;
                            nextHookIdx = i;
                        }
                    }
                    else
                    {
                        if (CP < 0)
                        {
                            nextTheta = theta;
                            nextHookIdx = i;
                        }
                    }
                }
            }

            if (nextHookIdx == -1)
            {
                if (lengthOfString < fabs(hooks[lastHookIdx].y) + EPSILON)
                    orbit = 2.0 * PI * lengthOfString;
                else
                {
                    orbit += lengthOfString * (rightmostAngle - lastTheta);
                    orbit *= 2.0;
                }

                cout << "Length of periodic orbit = ";
                cout << fixed << setprecision(2) << orbit << "\n\n";
                break;
            }

            orbit += lengthOfString * fabs(nextTheta - lastTheta);
            lengthOfString -= getDist(hooks[nextHookIdx], hooks[lastHookIdx]);
            lastHookIdx = nextHookIdx, lastTheta = nextTheta;
        }
    }

    return 0;
}
