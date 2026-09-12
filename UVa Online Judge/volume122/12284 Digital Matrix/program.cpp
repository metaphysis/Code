// Digital Matrix
// UVa ID: 12284
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.070s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> a[i][j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> b[i][j];
        bool same = true, symB = true;
        int diff = 0;
        vector<pair<int, int>> badA, badB;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (a[i][j] != b[i][j]) {
                    same = false;
                    diff++;
                }
            }
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                if (a[i][j] != a[j][i])
                    badA.push_back({i, j});
                if (b[i][j] != b[j][i]) {
                    symB = false;
                    badB.push_back({i, j});
                }
            }
        int ans;
        if (same)
            ans = 0;
        else if (symB)
            ans = -1;
        else {
            ans = diff;
            if (badA.size() == 1 && badB.size() == 1 && badA[0] == badB[0]) {
                int x = badA[0].first, y = badA[0].second;
                if (a[x][y] == b[y][x] && a[y][x] == b[x][y]) {
                    if (k >= 3)
                        ans++;
                    else if (n == 2)
                        ans = -1;
                    else
                        ans += 2;
                }
            }
        }
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
