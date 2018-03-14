// Square Sums
// UVa ID: 11470
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    int grid[16][16];

    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ":";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> grid[i][j];
        int x = 0, t = n / 2 - 1;
        while (x <= t)
        {
            int sum = 0;
            for (int i = x; i <= n - x - 1; i++)
                sum += grid[x][i] + grid[i][x] + grid[n - x - 1][i] + grid[i][n - x - 1];
            sum -= grid[x][x] + grid[n - x - 1][x] + grid[x][n - x - 1] + grid[n - x - 1][n - x - 1];
            cout << ' ' << sum;
            x++;
        }
        if (n & 1) cout << ' ' << grid[n / 2][n / 2];
        cout << '\n';
    }

    return 0;
}
