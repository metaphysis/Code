// Tour
// UVa ID: 1347
// Verdict: Accepted
// Submission Date: 2018-04-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    double x, y;
    bool operator<(const point &p) const
    {
        return x < p.x;
    }
} ps[1001];

double B[1001][1001];

double distTo(int i, int j)
{
    return sqrt(pow(ps[i].x - ps[j].x, 2) + pow(ps[i].y - ps[j].y, 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    
    while (cin >> n)
    {
        if (n == 1)
        {
            cout << "0.00\n";
            continue;
        }

        // BTSP.
        for (int i = 1; i <= n; i++) cin >> ps[i].x >> ps[i].y;
        sort(ps + 1, ps + n + 1);
        B[1][2] = distTo(1, 2);
        for (int j = 3; j <= n; j++)
        {
            for (int i = 1; i < j - 1; i++)
                B[i][j] = B[i][j - 1] + distTo(j - 1, j);
            B[j - 1][j] = 1e20;
            for (int k = 1; k < j - 1; k++)
                if (B[k][j - 1] + distTo(k, j) < B[j - 1][j])
                    B[j - 1][j] = B[k][j - 1] + distTo(k, j);
        }
        B[n][n] = B[n - 1][n] + distTo(n - 1, n);

        cout << fixed << setprecision(2) << B[n][n] << '\n';
    }

    return 0;
}
