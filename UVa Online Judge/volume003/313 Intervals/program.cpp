// Intervals
// UVa ID: 313
// Verdict: Accepted
// Submission Date: 2016-07-09
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double HALF_PI = acos(0.0);
const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct pipe
{
    double x, y, r;
};

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

        // a bit strict on float point number epsilon
        // avoid using triangle function
        vector < pair < double, double >>intervals;
        double a, b, c, left, right;

        for (int i = 0; i < pipes.size(); i++)
        {
            a = (pipes[i].x - light.x) * (pipes[i].x - light.x) - pipes[i].r * pipes[i].r;
            b = 2 * (pipes[i].x - light.x) * (light.y - pipes[i].y);
            c = (light.y - pipes[i].y) * (light.y - pipes[i].y) - pipes[i].r * pipes[i].r;
            if (b * b - 4 * a * c > 0)
            {
                if (fabs(a) >= EPSILON)
                {
                    double m1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
                    double m2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
                    double left, right;
                    c = light.y - m1 * light.x;
                    left = -c / m1;
                    c = light.y - m2 * light.x;
                    right = -c / m2;
                    if (left >= right)
                        swap(left, right);
                    intervals.push_back(make_pair(left, right));
                }
                else
                {
                    double m1 = -c / b;
                    c = light.y - m1 * light.x;
                    left = -c / m1;
                    right = light.x;
                    if (left >= right)
                        swap(left, right);
                    intervals.push_back(make_pair(left, right));
                }
            }
        }

        sort(intervals.begin(), intervals.end());

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
        cout << fixed << setprecision(2) << coverL << " " << coverR << endl;
        cout << endl;
    }

    return 0;
}
