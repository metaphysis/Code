// Period
// UVa ID: 1328
// Verdict: Accepted
// Submission Date: 2024-11-13
// UVa Run Time: 0.080s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000100;
const int BASE = 16777213, MOD = 2147483647;

long long h[MAXN], b[MAXN];

int N, cycle[MAXN], cases = 1;
string s;

void getHash() {
    h[0] = 0;
    int n = s.length();
    for (int i = 1; i <= n; i++)
        h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
}

int prepared = 0;

int getHash(int L, int R) {
    if (!prepared) {
        h[0] = 0, b[0] = 1;
        int n = s.length();
        for (int i = 1; i <= n; i++) {
            h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
            b[i] = b[i - 1] * BASE % MOD;
        }
        prepared = 1;
    }
    return (h[R + 1] - h[L] * b[R - L + 1] % MOD + MOD) % MOD;
}
    
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> N) {
        if (N == 0) break;
        cin >> s;
        getHash();
        prepared = 0;
        memset(cycle, 0, (N + 1) * sizeof(int));
        int cnt = 1;
        for (int i = 1; i <= N / 2; i++) {
            if (cnt == N) break;
            int hash = getHash(0, i - 1);
            for (int j = i + i; j <= N; j += i) {
                if (hash == getHash(j - i, j - 1)) {
                    if (cycle[j]) continue;
                    cnt++;
                    cycle[j] = j / i;
                } else break;
            }
        }
        cout << "Test case #" << cases++ << '\n';
        for (int i = 1; i <= N; i++)
            if (cycle[i] > 1)
                cout << i << ' ' << cycle[i] << '\n';
        cout << '\n';
    }
    return 0;
}
