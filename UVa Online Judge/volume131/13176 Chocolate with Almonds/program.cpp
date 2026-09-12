#include <bits/stdc++.h>
using namespace std;

int row, col, sum[21][21], memo[21][21][21][21];

bool same(int x1, int x2, int y1, int y2) {
    int cnt = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
    return cnt == 0 || cnt == area;
}

int solve(int x1, int x2, int y1, int y2) {
    int &ans = memo[x1][x2][y1][y2];
    if (ans != -1) return ans;
    if (same(x1, x2, y1, y2)) return ans = 0;
    ans = 1000000000;
    for (int i = x1; i < x2; i++) ans = min(ans, solve(x1, i, y1, y2) + solve(i + 1, x2, y1, y2) + 1);
    for (int i = y1; i < y2; i++) ans = min(ans, solve(x1, x2, y1, i) + solve(x1, x2, i + 1, y2) + 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> row >> col) {
        memset(sum, 0, sizeof(sum));
        memset(memo, -1, sizeof(memo));
        for (int i = 1; i <= row; i++) {
            string str;
            cin >> str;
            for (int j = 1; j <= col; j++) {
                int val = str[j - 1] == '#';
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + val;
            }
        }
        cout << solve(1, row, 1, col) << '\n';
    }
    return 0;
}
