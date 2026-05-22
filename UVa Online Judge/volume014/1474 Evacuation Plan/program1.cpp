// Evacuation Plan
// UVa ID: 1474
// Verdict: Accepted
// Submission Date: 2026-05-22
// UVa Run Time: 0.660s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 4005;
const ll INF = 1e18;

int n, m;
pair<int, int> team[MAXN];
pair<int, int> shelter[MAXN];
ll suf[MAXN][MAXN];
int teamPos[MAXN], shelterPos[MAXN], shelterId[MAXN];

void solve() {
    for (int i = 0; i < n; ++i) cin >> team[i].first, team[i].second = i;
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> shelter[i].first, shelter[i].second = i;
    sort(team, team + n);
    sort(shelter, shelter + m);
    for (int i = 0; i < n; ++i) teamPos[i] = team[i].first;
    for (int i = 0; i < m; ++i) shelterPos[i] = shelter[i].first, shelterId[i] = shelter[i].second;
    // 后缀DP
    suf[n - 1][m - 1] = abs(teamPos[n - 1] - shelterPos[m - 1]);
    for (int i = n - 2; i >= 0; --i) suf[i][m - 1] = suf[i + 1][m - 1] + abs(teamPos[i] - shelterPos[m - 1]);
    for (int i = n - 2; i >= 0; --i)
        for (int j = m - 2; j >= 0; --j) {
            ll cost = abs(teamPos[i] - shelterPos[j]);
            suf[i][j] = cost + suf[i + 1][j + 1];
            if (n - i > m - j) suf[i][j] = min(suf[i][j], cost + suf[i + 1][j]);
        }
    cout << suf[0][0] << '\n';
    // 贪心构造
    vector<int> ans(n);
    for (int i = 0, j = 0; i < n; ++i) {
        ans[team[i].second] = shelterId[j] + 1;
        if (j + 1 < m && n - i > m - j && suf[i + 1][j] > suf[i + 1][j + 1]) j++;
        else if (n - i == m - j) j++;
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " \n"[i == n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n) solve();
    return 0;
}
