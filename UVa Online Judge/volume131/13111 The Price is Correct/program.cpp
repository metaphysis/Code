#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    while (test--) {
        int n, m, p;
        cin >> n >> m >> p;
        int x0, y0;
        cin >> x0 >> y0;
        --x0;
        --y0;
        vector<vector<vector<int>>> prize(2 * p + 1, vector<vector<int>>(n, vector<int>(m, 0)));
        for (int k = 0; k < p; ++k) {
            int x, y, time, value;
            cin >> x >> y >> time >> value;
            prize[time][x - 1][y - 1] = value;
        }
        const int neg = -1000000000;
        vector<vector<int>> pre(n, vector<int>(m, neg)), cur(n, vector<int>(m, neg));
        pre[x0][y0] = 0;
        int dx[5] = {-1, 1, 0, 0, 0}, dy[5] = {0, 0, -1, 1, 0};
        for (int time = 1; time <= 2 * p; ++time) {
            for (int i = 0; i < n; ++i)
                fill(cur[i].begin(), cur[i].end(), neg);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    for (int d = 0; d < 5; ++d) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni < 0 || ni >= n || nj < 0 || nj >= m)
                            continue;
                        cur[i][j] = max(cur[i][j], pre[ni][nj]);
                    }
                    if (cur[i][j] != neg)
                        cur[i][j] += prize[time][i][j];
                }
            }
            swap(pre, cur);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans = max(ans, pre[i][j]);
        cout << ans << '\n';
    }
    return 0;
}
