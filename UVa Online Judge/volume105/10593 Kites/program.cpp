// Kites
// UVa ID: 10593
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510;
char g[MAXN][MAXN];
int s[MAXN][MAXN], d[MAXN][MAXN];
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> g[i][j];
        memset(s, 0, sizeof s);
        memset(d, 0, sizeof d);
        int r = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (g[i][j] == 'x') {
                    // 正方形：以(i,j)为右下角的最大正方形边长
                    s[i][j] = min({s[i - 1][j], s[i][j - 1]});
                    if (g[i - s[i][j]][j - s[i][j]] == 'x') s[i][j]++;
                    // 菱形：以(i,j)为最下顶点的最大菱形尺寸
                    d[i][j] = min({d[i - 1][j - 1], d[i - 1][j], d[i - 1][j + 1]});
                    if (g[i - 2 * d[i][j]][j] == 'x') d[i][j]++;
                    // 统计边长大于 1 的正方形和菱形数量
                    r += s[i][j] + d[i][j] - 2;
                }
        cout << r << '\n';
    }
    return 0;
}
