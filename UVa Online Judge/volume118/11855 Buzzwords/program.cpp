// Buzzwords
// UVa ID: 11855
// Verdict: Accepted
// Submission Date: 2023-07-09
// UVa Run Time: 0.250s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int BASE = 16777213, MOD = 2147483647;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        string s;
        for (auto c : line) if (c != ' ') s += c;
        int n = (int)s.length();
        long long h[1010], b[1010];
        h[0] = 0, b[0] = 1;
        for (int i = 1; i <= 1000; i++) b[i] = b[i - 1] * BASE % MOD;
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
        bool empty = 0;
        for (int i = 1; i <= n; i++) {
            map<long long, int> mp;
            for (int j = 0; j + i - 1 < n; j++) {
                long long sh = (h[j + i] - h[j] * b[i] % MOD + MOD) % MOD;
                mp[sh]++;
            }
            int r = 0;
            for (auto p : mp) r = max(r, p.second);
            if (r > 1) { cout << r << '\n'; empty = 0; }
            else {
                if (!empty) cout << '\n';
                empty = 1;
            }
        }
    }
    return 0;
}
