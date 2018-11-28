// Colliding Traffic
// UVa ID: 11574
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.240s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0), EPSILON = 1e-8;

struct boat
{
    double x, y, d, s;
} boats[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, n;
    double r;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n >> r;
        for (int i = 0; i < n; i++)
        {
            cin >> boats[i].x >> boats[i].y >> boats[i].d >> boats[i].s;
            boats[i].d = PI * boats[i].d / 180.0;
        }
        bool collided = false;
        double seconds = 1e10;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                double a = pow(boats[i].s * sin(boats[i].d) - boats[j].s * sin(boats[j].d), 2) + pow(boats[i].s * cos(boats[i].d) - boats[j].s * cos(boats[j].d), 2);
                double b = 2 * (boats[i].s * sin(boats[i].d) - boats[j].s * sin(boats[j].d)) * (boats[i].x - boats[j].x) + 2 * (boats[i].s * cos(boats[i].d) - boats[j].s * cos(boats[j].d)) * (boats[i].y - boats[j].y);
                double c = pow(boats[i].x - boats[j].x, 2) + pow(boats[i].y - boats[j].y, 2);
                double d;
                if (fabs(a) < EPSILON) d = sqrt(c);
                else
                {
                    if (b < 0)
                        d = sqrt(fabs((4 * a * c - b * b) / (4 * a)));
                    else
                        d = sqrt(c);
                }
                if (d < r)
                {
                    collided = true;
                    if (fabs(a) < EPSILON) seconds = 0;
                    else
                    {
                        c -= r * r;
                        double root1 = (-b + sqrt(fabs(b * b - 4 * a * c))) / 2 / a;
                        double root2 = (-b - sqrt(fabs(b * b - 4 * a * c))) / 2 / a;
                        seconds = min(seconds, max(0.0, min(root1, root2)));
                    }
                }
            }
        if (!collided) cout << "No collision.\n";
        else cout << fixed << setprecision(0) << seconds << '\n';
    }

    return 0;
}
