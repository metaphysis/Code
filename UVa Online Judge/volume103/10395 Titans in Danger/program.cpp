// Titans in Danger
// UVa ID: 10395
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// Heap排列生成算法
void dfs(int n, string &s) {
    if (n == 1) { cout << s << '\n'; return; }
    dfs(n - 1, s);
    for (int i = 0; i < n - 1; ++i) {
        swap(s[(n & 1) ? 0 : i], s[n - 1]);
        dfs(n - 1, s);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) { dfs(s.size(), s); cout << '\n'; }
}
