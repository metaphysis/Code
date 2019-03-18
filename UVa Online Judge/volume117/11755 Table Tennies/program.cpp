// Table Tennis
// UVa ID: 11755
// Verdict: Accepted
// Submission Date: 2019-03-18
// UVa Run Time: 0.060s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-8;

double dp[24][24][100], p1, p2;

double dfs(int win, int lose, int depth)
{
    if (depth >= 100) return 0;
    if (dp[win][lose][depth] >= 0) return dp[win][lose][depth];
    if (win == 21) return 1.0;
    if (lose == 21) return 0;
    if (win == lose && win == 20) return dfs(15, 15, depth + 1);
    double r = 0;
    int round = (win + lose) % 10;
    if (0 <= round && round <= 4)
        r = p1 * dfs(win + 1, lose, depth) + (1.0 - p1) * dfs(win, lose + 1, depth);
    else
        r = p2 * dfs(win + 1, lose, depth) + (1.0 - p2) * dfs(win, lose + 1, depth);
    return dp[win][lose][depth] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case " << cs << ": ";
        string status;
        cin.ignore(256, '\n');
        getline(cin, status);
        cin >> p1 >> p2;
        int win = 0, lose = 0, valid = 1;
        for (int i = 0; i < status.length(); i++)
        {
            int p = i % 10;
            if (0 <= p && p <= 4)
            {
                if (fabs(1.0 - p1) <= EPSILON && status[i] == 'L') valid = 0;
                if (fabs(p1) <= EPSILON && status[i] == 'W') valid = 0;
            }
            else
            {
                if (fabs(1.0 - p2) <= EPSILON && status[i] == 'L') valid = 0;
                if (fabs(p2) <= EPSILON && status[i] == 'W') valid = 0;
            }
            if (status[i] == 'W') win += 1;
            else lose += 1;
            if ((win == 21 || lose == 21) && i < status.length() - 1) valid = 0;
            if (win == 20 && lose == 20) win = lose = 15;
            if (!valid) break;
        }
        if (!valid)
        {
            cout << "-1.000000\n";
            continue;
        }
        for (int i = 0; i < 24; i++)
            for (int j = 0; j < 24; j++)
                for (int k = 0; k < 100; k++)
                    dp[i][j][k] = -1;
        cout << fixed << setprecision(6) << dfs(win, lose, 0) << '\n';
    }

    return 0;
}
