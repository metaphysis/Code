// Bright Lights
// UVa ID: 10927
// Verdict: Accepted
// Submission Date: 2017-12-07
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y, z;
    double poleAngle;
    point (int x = 0, int y = 0): x(x), y(y) {}
    bool operator<(const point &p) const
    {
        if (poleAngle != p.poleAngle) return poleAngle < p.poleAngle;
        // use long long, -100000<=X<= 100000, so x*x may exceed range of int
        long long dist1 = (long long)x * x + (long long)y * y;
        long long dist2 = (long long)p.x * p.x + (long long)p.y * p.y;
        return dist1 < dist2;
    }
}ps[100010];

bool cmp(point &a, point &b)
{
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> ps[i].x >> ps[i].y >> ps[i].z;
            ps[i].poleAngle = atan2(ps[i].y, ps[i].x);
        }

        sort(ps, ps + n);

        vector<point> invisible;

        int heightMost = ps[0].z;
        for (int i = 1; i < n; i++)
        {
            if (ps[i].poleAngle != ps[i - 1].poleAngle)
                heightMost = ps[i].z;
            else
            {
                if (ps[i].z <= heightMost)
                    invisible.push_back(ps[i]);
                else
                    heightMost = ps[i].z;
            }
        }

        sort(invisible.begin(), invisible.end(), cmp);

        cout << "Data set " << ++cases << ":\n";
        if (!invisible.size())
        {
            cout << "All the lights are visible.\n";
        }
        else
        {
            cout << "Some lights are not visible:\n";
            for (int i = 0; i < invisible.size(); i++)
            {
                if (i) cout << ";\n";
                cout << "x = " << invisible[i].x << ", y = " << invisible[i].y;
            }
            cout << ".\n";
        }
    }

    return 0;
}
