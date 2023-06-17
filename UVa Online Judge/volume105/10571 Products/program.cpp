// Products
// UVa ID: 10571
// Verdict: Accepted
// Submission Date: 2023-06-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int n, cln[16][2], row[16][2], cv[16][2], rv[16][2], cnt[16];
int found, used[1024];
int X[16], Y[16];
vector<pair<int, int>> y[16];

void dfs(int idx) {
    if (found) return;
    if (idx == n) {
        int g[16][16] = {0};
        for (int i = 0; i < n; i++) {
            g[i][row[i][0]] = rv[i][0];
            g[i][row[i][1]] = rv[i][1];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j) cout << ' ';
                cout << g[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
        found = 1;
        return;
    }
    for (auto p : y[idx]) {
        for (int i = 0; i < n; i++) {
            if (X[i] % p.first != 0) continue;
            if (cnt[i] > 1) continue;
            if (used[p.first]) continue;
            if (cnt[i] && cv[i][0] * p.first != X[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (X[j] % p.second != 0) continue;
                if (cnt[j] > 1) continue;
                if (used[p.second]) continue;
                if (cnt[j] && cv[j][0] * p.second != X[j]) continue;
                row[idx][0] = i, row[idx][1] = j;
                rv[idx][0] = p.first, rv[idx][1] = p.second;
                cln[i][cnt[i]] = idx, cln[j][cnt[j]] = idx;
                cv[i][cnt[i]] = p.first, cv[j][cnt[j]] = p.second;
                cnt[i]++, cnt[j]++;
                used[p.first] = used[p.second] = 1;
                dfs(idx + 1);
                cnt[i]--, cnt[j]--;
                used[p.first] = used[p.second] = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) cin >> X[i];
        for (int i = 0; i < n; i++) {
            cin >> Y[i];
            y[i].clear();
            for (int j = 1; j <= Y[i]; j++)
                if (Y[i] % j == 0 && j != Y[i] / j)
                    y[i].push_back(make_pair(j, Y[i] / j));
        }
        memset(cnt, found = 0, sizeof cnt);
        memset(used, 0, sizeof used);
        dfs(0);
    }
    return 0;
}
