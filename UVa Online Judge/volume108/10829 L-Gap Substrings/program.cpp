// L-Gap Substrings
// UVa ID: 10829
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 1.740s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const int MAXN = 50005;
const ull BASE = 131;

ull powBase[MAXN];
ull preHash[MAXN];

void initHash(const string &s) {
    int n = s.length();
    powBase[0] = 1;
    for (int i = 1; i <= n; ++i) powBase[i] = powBase[i-1] * BASE;
    preHash[0] = 0;
    for (int i = 1; i <= n; ++i) preHash[i] = preHash[i-1] * BASE + (s[i-1] - 'a' + 1);
}

ull getHash(int l, int r) { // 闭区间 [l, r]，0-based
    return preHash[r+1] - preHash[l] * powBase[r-l+1];
}

int countGapSubstrings(int g, const string &s) {
    int n = s.length();
    initHash(s);
    int ans = 0;
    for (int lenU = 1; lenU <= (n - g) / 2; ++lenU) {
        for (int i = 0; i + 2 * lenU + g <= n; ++i) {
            int j = i + lenU + g;
            if (getHash(i, i + lenU - 1) == getHash(j, j + lenU - 1)) ++ans;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        int g;
        string s;
        cin >> g >> s;
        int ans = countGapSubstrings(g, s);
        cout << "Case " << caseNo << ": " << ans << "\n";
    }
    return 0;
}
