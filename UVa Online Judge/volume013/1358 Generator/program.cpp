// Generator
// UVa ID: 1358
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163216588

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        string s;
        cin >> N >> s;
        int m = (int)s.size();
        // 计算 KMP 前缀函数，nxt[i] 表示长度为 i 的前缀的 border 长度
        vector<int> nxt(m + 1, 0);
        for (int i = 1; i < m; ++i) {
            int j = nxt[i];
            while (j > 0 && s[i] != s[j]) j = nxt[j];
            if (s[i] == s[j]) ++j;
            nxt[i + 1] = j;
        }
        vector<ll> f(m + 1, 0); // f[0] = 0
        for (int i = 0; i < m; ++i) {
            f[i + 1] = (f[i] + 1) * (ll)N;
            for (int c = 0; c < N; ++c) {
                if (s[i] == char('A' + c)) continue;
                int k = nxt[i];
                while (k > 0 && s[k] != char('A' + c)) k = nxt[k];
                if (s[k] == char('A' + c)) ++k;
                f[i + 1] -= f[k];
            }
        }
        if (caseNo > 1) cout << '\n';
        cout << "Case " << caseNo << ":\n";
        cout << f[m] << '\n';
    }
    return 0;
}
