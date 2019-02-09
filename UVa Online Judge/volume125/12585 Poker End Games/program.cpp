// Poker End Games
// UVa ID: 12585
// Verdict: Accepted
// Submission Date: 2019-02-09
// UVa Run Time: 0.050s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int visited[310][310][30];
pair<double, double> dp[310][310][30];

pair<double, double> dfs(int a, int b, int depth)
{
    if (depth >= 30) return make_pair(0.0, 0.0);
    if (a == 0) return make_pair(0.0, 0.0);
    if (b == 0) return make_pair(0.0, 1.0);
    if (visited[a][b][depth]) return dp[a][b][depth];
    visited[a][b][depth] = 1;
    pair<double, double> r1 = dfs(a + min(a, b), b - min(a, b), depth + 1);
    pair<double, double> r2 = dfs(a - min(a, b), b + min(a, b), depth + 1);
    return dp[a][b][depth] = make_pair(0.5 * r1.first + 0.5 * r2.first + 1, 0.5 * r1.second + 0.5 * r2.second);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, a, b;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a >> b;
        memset(visited, 0, sizeof(visited));
        pair<double, double> r = dfs(a, b, 1);
        cout << "Case " << cs << ": ";
        cout << fixed << setprecision(6) << r.first;
        cout << ' ' << r.second << endl;
    }

    return 0;
}
