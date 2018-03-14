// Term Strategy
// UVa ID: 11341
// Verdict: Accepted
// Submission Date: 2017-11-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, m, grade[11][110], sum[11][110];
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;

        int t = 0;
        for (int i = 1; i <= n; i++)
        {
            bool flag = false;
            for (int j = 1; j <= m; j++)
            {
                cin >> grade[i][j];
                if (t >= 0 && !flag && grade[i][j] >= 5) t += j, flag = true;
            }
            if (!flag) t = -1;
        }

        if (t < 0 || t > m)
        {
            cout << "Peter, you shouldn't have played billiard that much.\n";
            continue;
        }

        memset(sum, -1, sizeof(sum));
        sum[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int k = i; k <= i + m - n; k++)
                for (int j = 1; j <= k - i + 1; j++)
                    if (grade[i][j] >= 5 && sum[i - 1][k - j] >= 0)
                        sum[i][k] = max(sum[i][k], sum[i - 1][k - j] + grade[i][j]);

        cout << "Maximal possible average mark - ";
        cout << fixed << setprecision(2) << (1.0 * sum[n][m] / n + 1e-9) << ".\n";
    }

    return 0;
}
