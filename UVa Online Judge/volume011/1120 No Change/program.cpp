// No Change
// UVa ID: 1120
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int x, k;
vector<int> values;
bool found;

void dfs(int idx, int remaining, int prevCount) {
    if (found) return;
    if (idx == k) {
        if (remaining == 0) found = true;
        return;
    }
    int maxCount = min(prevCount, remaining / values[idx]);
    for (int count = maxCount; count >= 0; --count) {
        dfs(idx + 1, remaining - count * values[idx], count);
        if (found) return;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> x >> k;
        values.resize(k);
        for (int i = 0; i < k; ++i)
            cin >> values[i];
        found = false;
        dfs(0, x, x / values[0] + 1); // 初始 prevCount 设为最大可能值
        cout << (found ? "YES" : "NO") << endl;
        if (t) cout << endl;
    }
    return 0;
}
