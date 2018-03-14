// Yoyodyne Propulsion Systems
// UVa ID: 10832
// Verdict: Accepted
// Submission Date: 2017-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    double x, y, z;
    point(double x = 0, double y = 0, double z = 0):x(x), y(y), z(z) {}
    point operator+(const point & p) const { return point(x + p.x, y + p.y, z + p.z); }
    point operator-(const point & p) const { return point(x - p.x, y - p.y, z - p.z); }
    point operator*(const double u) const {return point(x * u, y * u, z * u); }
    double distTo(const point & p) { return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2)); }
}ps[21];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    point pc;
    int f, b, r, n, visited[21], sequence[21], buoys;
    int cases = 0;

    while (cin >> f >> b >> r >> n, f > 0)
    {
        cases++;

        for (int i = 0; i < n; i++)
            cin >> ps[i].x >> ps[i].y >> ps[i].z;

        buoys = 0;
        pc = point(0, 0, 1);
        memset(visited, 0, sizeof(visited));

        while (buoys < n)
        {
            int mini = -1;
            double dist = -1;
            for (int i = 0; i < n; i++)
            {
                if (visited[i])
                    continue;
                double temp = pc.distTo(ps[i]);
                if (dist < 0 || temp < dist)
                {
                    mini = i;
                    dist = temp;
                }
            }
            pc = ps[mini];
            visited[mini] = 1;
            sequence[buoys++] = mini;
        }

        buoys = 0;
        pc = point(0, 0, 1);
        double time = 0.0, traveled = 0.0, fuel = f, home;

        while (buoys < n)
        {
            double dist = pc.distTo(ps[sequence[buoys]]);
            double forward = fuel / b * r;

            if (forward >= dist)
            {
                traveled += dist;
                time += dist / r;
                fuel -= (dist / r) * b;
            }
            else
            {
                traveled += forward;
                time += fuel / b;
                pc = pc + (ps[sequence[buoys]] - pc) * (forward / dist);
                home = pc.distTo(ps[sequence[n - 1]]);
                break;
            }
            pc = ps[sequence[buoys++]];
        }

        if (buoys == n)
        {
            cout << "Mission " << cases;
            cout << ": SUCCESS!! Time: ";
            cout << fixed << setprecision(2) << time;
            cout << "  Traveled: ";
            cout << fixed << setprecision(2) << traveled;
            cout << "  Fuel Left: ";
            cout << fixed << setprecision(2) << fuel << '\n';
        }
        else
        {
            cout << "Mission " << cases;
            cout << ": FAILURE!! Traveled: ";
            cout << fixed << setprecision(2) << traveled;
            cout << "  From Home: ";
            cout << fixed << setprecision(2) << home << '\n';
        }
    }

    return 0;
}
