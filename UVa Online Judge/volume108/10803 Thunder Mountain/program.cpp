// Thunder Mountain
// UVa ID: 10803
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

struct point
{
    int x, y;
    int distTo(point &p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
} ps[MAXV];

int n;
double dist[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            dist[i][i] = 0;
            cin >> ps[i].x >> ps[i].y;
        }
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                int d = ps[i].distTo(ps[j]);
                if (d <= 100)
                    dist[i][j] = dist[j][i] = sqrt(d);
                else
                    dist[i][j] = dist[j][i] = 1e10;
            }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        double longest = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                longest = max(longest, dist[i][j]);

        cout << "Case #" << c << ":\n";
        if (longest == 1e10) cout << "Send Kurdy";
        else cout << fixed << setprecision(4) << longest;
        cout << "\n\n";
    }

    return 0;
}
