// Flight Planning
// UVa ID: 801
// Verdict: Accepted
// Submission Date: 2018-12-29
// UVa Run Time: 0.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int K, best[128][32];
double dp[128][32], length[128], winddown[128], windup[128];

double dfs(int leg, int altitude)
{
    if (leg == K) return 0;
    if (dp[leg][altitude] >= 0) return dp[leg][altitude];
    double r = 1e20;
    for (int i = 0; i <= 20; i++)
    {
        double cost = 0;
        if (i > altitude) cost += 50.0 * fabs(i - altitude);
        cost += (fabs(i - 10) * 10.0 + 2000.0) * (length[leg] / (400.0 + winddown[leg] + (windup[leg] - winddown[leg]) * i / 20.0));
        cost += dfs(leg + 1, i);
        if (cost < r)
        {
            r = cost;
            best[leg][altitude] = i;
        }
    }
    return dp[leg][altitude] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> K;
        for (int i = 0; i < K; i++)
            cin >> length[i] >> winddown[i] >> windup[i];
        for (int i = 0; i < K; i++)
            for (int j = 0; j <= 20; j++)
                dp[i][j] = -1;
        cout << "Flight " << cs << ": ";
        double fuel = dfs(0, 0);
        int altitude = 0;
        for (int i = 0; i < K; i++)
        {
            cout << (20 + best[i][altitude]) << ' ';
            altitude = best[i][altitude];
        }
        // Round up but not round to nearest gallons leads to AC.
        cout << fixed << setprecision(0) << (fuel + 1000.5) << '\n';
    }

    return 0;
}
