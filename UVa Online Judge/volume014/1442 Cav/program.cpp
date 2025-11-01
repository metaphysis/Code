// Cav
// UVa ID: 1442
// Verdict: Accepted
// Submission Date: 2025-11
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int Z;
    cin >> Z;
    while (Z--) {
        int n;
        cin >> n;
        vector<int> p(n), s(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        for (int i = 0; i < n; ++i) cin >> s[i];
        vector<int> level(n);
        int cur = s[0];
        for (int i = 0; i < n; ++i) {
            if (cur > s[i]) cur = s[i];
            if (cur < p[i]) cur = p[i];
            level[i] = cur;
        }
        cur = s[n - 1];
        for (int i = n - 1; i >= 0; --i) {
            if (cur > s[i]) cur = s[i];
            if (cur < p[i]) cur = p[i];
            level[i] = min(level[i], cur);
        }
        long long area = 0;
        for (int i = 0; i < n; ++i)
            area += level[i] - p[i];
        cout << area << "\n";
    }
    return 0;
}
