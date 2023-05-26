// Binary Search Tree
// UVa ID: 1264
// Verdict: Accepted
// Submission Date: 2023-05-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>

using namespace std;

const int MAXN = 32, MOD = 9999991;
int T[MAXN][2], C[32][32], S[MAXN];

long long dfs(int u) {
    if (S[u] <= 1) return 1;
    long long r = dfs(T[u][0]) * dfs(T[u][1]); r %= MOD;
    r *= C[S[u] - 1][S[T[u][0]]]; r %= MOD;
    return r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    C[0][0] = 1;
    for (int i = 1; i <= 20; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    int cases; cin >> cases;
    while (cases--) {
        int n; cin >> n;
        int R; cin >> R;
        memset(T, 0, sizeof T);
        memset(S, 0, sizeof S);
        S[R] = 1;
        for (int i = 1, x; i < n; i++) {
            cin >> x;
            S[x] = 1;
            int nd = R;
            while (true) {
                S[nd]++;
                if (x < nd) {
                    if (!T[nd][0]) { T[nd][0] = x; break; }
                    nd = T[nd][0];
                }
                else {
                    if (!T[nd][1]) { T[nd][1] = x; break; }
                    nd = T[nd][1];
                }
            }
        }
        cout << dfs(R) << '\n';
    }
}
