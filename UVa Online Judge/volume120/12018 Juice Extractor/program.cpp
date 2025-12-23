// Juice Extractor
// UVa ID: 12018
// Verdict: Accepted
// Submission Date: 2025-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
struct Fruit { int start, end; } fruits[MAXN];
int dp[MAXN], n;

int dfs(int p) {
    if (p == -1) return 0;
    if (~dp[p]) return dp[p];
    // 第 p 个水果的出现时间不切割
    int r = dfs(p - 1);
    // 第 p 个水果的出现时间作为切割时间
    int cnt = 0;
    for (int i = p; i >= 0; i--) {
        if (fruits[i].end >= fruits[p].start) cnt++;
        if ((!i || fruits[i - 1].start != fruits[i].start) && cnt > 2)
            r = max(r, dfs(i - 1) + cnt);
    }
    return dp[p] = r;
}

int main() {
    int t; cin >> t;
    for (int caseId = 1; caseId <= t; ++caseId) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> fruits[i].start >> fruits[i].end;
        sort(fruits, fruits + n, [](const Fruit& a, const Fruit& b) {
            if (a.start != b.start) return a.start < b.start;
            return a.end < b.end;
        });
        memset(dp, -1, sizeof dp);
        cout << "Case #" << caseId << ": " << dfs(n - 1) << '\n';
    }
    return 0;
}
