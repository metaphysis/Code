// The Knight'cnt Tour
// UVa ID: 10255
// Verdict: Wrong Answer
// Submission Date: 2019-08-16
// UVa Run Time: 0.040S
//
// 参考：
// https://github.com/dk00/miscellanea/blob/e1184684c85fe9bbd1ceba58b94d4da84c67784e/uva/c/10255.cpp

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64, INF = 0x3f3f3f3f;

int cnt[MAXN][MAXN], number[MAXN][MAXN], idx, n, lastr, lastc;
int dr[8] = { 1, 2, 1, 2, -1, -2, -1, -2 }, dc[8] = { 2, 1, -2, -1, 2, 1, -2, -1 };

bool dfs(int r, int c)
{
    if (cnt[r][c] > 8) return false;
    number[r][c] = idx++;
    cnt[r][c] = INF;
    if (idx > n * n)
    {
        lastr = r, lastc = c;
        return true;
    }
    int minIdx = -1;
    for (int i = 0; i < 8; i++)
        if (r + dr[i] < n && r + dr[i] >= 0 && c + dc[i] < n && c + dc[i] >= 0)
        {
            minIdx = i;
            break;
        }
    if (minIdx == -1) return false;
    cnt[r + dr[minIdx]][c + dc[minIdx]]--;
    for (int i = minIdx + 1; i < 8; i++)
        if (r + dr[i] < n && r + dr[i] >= 0 && c + dc[i] < n && c + dc[i] >= 0)
        {
            cnt[r + dr[i]][c + dc[i]]--;
            if (cnt[r + dr[minIdx]][c + dc[minIdx]] > cnt[r + dr[i]][c + dc[i]])
                minIdx = i;
        }
    return dfs(r + dr[minIdx], c + dc[minIdx]);
}

// Warnsdorff's Rule.
void initialize()
{
    idx = 1;
    memset(cnt, 0, sizeof(cnt));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            for (int k = 0; k < 8; k++)
            {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n)
                    cnt[nr][nc]++;
            }
}

int main(int argc, char *argv[])
{
    int r, c, cases = 0;
    while (cin >> n >> r >> c)
    {
        if (cases++) cout << '\n';
        if (n == 1)
        {
            cout << "    1\n";
            continue;
        }
        if (n <= 5 || n % 2 == 1)
        {
            cout << "No Circuit Tour.\n";
            continue;
        }
        while (true)
        {
            initialize();
            if (dfs(0, 0)) break;
        }
        int delta = number[r - 1][c - 1], mod = n * n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << setw(5) << right << ((number[i][j] - delta + mod) % mod + 1);
            cout << '\n';
        }
    }
}
