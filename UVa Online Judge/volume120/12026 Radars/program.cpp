#include <bits/stdc++.h>
using namespace std;

int solve() {
    int n, ans = 0;
    cin >> n;
    vector<vector<int> > mat(n, vector<int>(n));
    vector<vector<bool> > vis(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> mat[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0)
                continue;
            long long sum = 0, cnt = 0;
            if (i > 0) {
                sum += mat[i - 1][j];
                cnt++;
            }
            if (i + 1 < n) {
                sum += mat[i + 1][j];
                cnt++;
            }
            if (j > 0) {
                sum += mat[i][j - 1];
                cnt++;
            }
            if (j + 1 < n) {
                sum += mat[i][j + 1];
                cnt++;
            }
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++) {
                    long long dx = x - i, dy = y - j;
                    long long dis = dx * dx + dy * dy;
                    if (dis * cnt * cnt <= sum * sum)
                        vis[x][y] = true;
                }
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!vis[i][j])
                ans++;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        cout << solve() << endl;
    return 0;
}
