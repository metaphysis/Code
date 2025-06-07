// The Longest Constant Gene
// UVa ID: 1227
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
const long long BASE = 43, MOD = 1000000007;
int h[7][MAXN], p[MAXN], L[16];

int getHash(int idx, int l, int r) {
    int v = h[idx][r + 1] - (1LL * p[r - l + 1] * h[idx][l]) % MOD;
    if (v < 0) v += MOD;
    return v;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    p[0] = 1;
    for (int i = 1; i < MAXN; i++) p[i] = (p[i - 1] * BASE) % MOD;
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int minL = INT_MAX;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            L[i] = s.length();
            h[i][0] = 0;
            for (int j = 1; j <= L[i]; j++) h[i][j] = (h[i][j - 1] * BASE + s[j - 1]) % MOD;
            minL = min(minL, L[i]);
        }
        int low = 0, high = minL, r;
        while (low <= high) {
            int middle = (low + high) >> 1;
            unordered_set<int> s1;
            for (int i = 0; i + middle - 1 < L[0]; i++) s1.insert(getHash(0, i, i + middle - 1));
            for (int i = 1; i < n; i++) {
                unordered_set<int> s2;
                for (int j = 0; j + middle - 1 < L[i]; j++) {
                    int k = getHash(i, j, j + middle - 1);
                    if (s1.find(k) != s1.end()) s2.insert(k);
                }
                s1 = s2;
                if (!s1.size()) break;
            }
            if (s1.size()) { low = middle + 1; r = middle; }
            else high = middle - 1;
        }
        cout << r << '\n';
    }
    return 0;
}
