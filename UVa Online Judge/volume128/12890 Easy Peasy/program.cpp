// Easy Peasy
// UVa ID: 12890
// Verdict: Accepted
// Submission Date: 2026-02-02
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    unordered_map<long long, int> lastPos;
    long long ans = 0;
    int left = 0;
    for (int right = 0; right < n; ++right) {
        if (lastPos.find(arr[right]) != lastPos.end() && lastPos[arr[right]] >= left)
            left = lastPos[arr[right]] + 1;
        lastPos[arr[right]] = right;
        ans += right - left + 1;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
