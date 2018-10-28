// Game of Sum
// UVa ID: 10891
// Verdict: Accepted
// Submission Date: 2018-10-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;
int n, visited[110][110];
int xi[110], sum[110], mx[110][110], mi[110][110];

void dfs(int i, int j)
{
    if (visited[i][j] || i > j) return;
    visited[i][j] = 1;
    int rmx = -INF, rmi = INF;
    for (int k = i; k <= j; k++)
    {
        int s = sum[k] - sum[i - 1];
        dfs(k + 1, j);
        if (s + mi[k + 1][j] > rmx)
        {
            rmx = s + mi[k + 1][j];
            rmi = mx[k + 1][j];
        }
        s = sum[j] - sum[k - 1];
        dfs(i, k - 1);
        if (s + mi[i][k - 1] > rmx)
        {
            rmx = s + mi[i][k - 1];
            rmi = mx[i][k - 1];
        }
    }
    mx[i][j] = rmx, mi[i][j] = rmi;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; i++)
        {
            cin >> xi[i];
            sum[i] = xi[i] + sum[i - 1];
        }
        memset(visited, 0, sizeof(visited));
        memset(mx, 0, sizeof(mx));
        memset(mi, 0, sizeof(mi));
        dfs(1, n);
        cout << (mx[1][n] - mi[1][n]) << '\n';
    }

    return 0;
}
