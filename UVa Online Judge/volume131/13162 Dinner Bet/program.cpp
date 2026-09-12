#include <bits/stdc++.h>
using namespace std;

long double cb[51][11], dp[11][11][11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cb[0][0] = 1;
    for (int i = 1; i <= 50; ++i) {
        cb[i][0] = 1;
        for (int j = 1; j <= min(i, 10); ++j)
            cb[i][j] = cb[i - 1][j - 1] + cb[i - 1][j];
    }
    int n, d, c;
    while (cin >> n >> d >> c) {
        bool has[51] = {};
        int val, same = 0;
        for (int i = 0; i < c; ++i) {
            cin >> val;
            has[val] = true;
        }
        for (int i = 0; i < c; ++i) {
            cin >> val;
            if (has[val]) ++same;
        }
        memset(dp, 0, sizeof(dp));
        int only = c - same, lim = 2 * only + same;
        long double den = cb[n][d];
        for (int sum = 0; sum <= lim; ++sum) {
            for (int x = 0; x <= only; ++x) {
                for (int y = 0; y <= only; ++y) {
                    for (int z = 0; z <= same; ++z) {
                        if (x + y + z != sum || x + z == 0 || y + z == 0) continue;
                        long double stay = 0, res = 0;
                        for (int i = 0; i <= x; ++i) {
                            for (int j = 0; j <= y; ++j) {
                                for (int k = 0; k <= z; ++k) {
                                    int rest = d - i - j - k, other = n - x - y - z;
                                    if (rest < 0 || rest > other) continue;
                                    long double prob = cb[x][i] * cb[y][j] * cb[z][k] * cb[other][rest] / den;
                                    if (i == 0 && j == 0 && k == 0) stay += prob;
                                    else res += prob * dp[x - i][y - j][z - k];
                                }
                            }
                        }
                        dp[x][y][z] = (1 + res) / (1 - stay);
                    }
                }
            }
        }
        cout << fixed << setprecision(5) << (double)dp[only][only][same] << '\n';
    }
    return 0;
}
