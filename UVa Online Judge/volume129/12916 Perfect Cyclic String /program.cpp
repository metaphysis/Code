// Perfect Cyclic String 
// UVa ID: 12916
// Verdict: Accepted
// Submission Date: 2023-07-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h> 
using namespace std;
const int BASE = 16777213, MOD = 2147483647;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    string s;
    long long h[1010], b[1010];
    b[0] = 1;
    for (int i = 1; i <= 1000; i++) b[i] = b[i - 1] * BASE % MOD;
    while (T--) {
        cin >> s;
        int n = (int)s.length();
        h[0] = 0;
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
        for (int i = 1; i <= n; i++) {
            if (n % i) continue;
            long long sh = h[i];
            bool flag = 1;
            for (int j = i + 1; j + i - 1 <= n && flag; j += i) {
                long long nh = (h[j + i - 1] - h[j - 1] * b[i] % MOD + MOD) % MOD;
                if (sh != nh) flag = 0;
            }
            if (flag) {
                cout << i << '\n';
                break;
            }
        }
    }
    return 0;
}
