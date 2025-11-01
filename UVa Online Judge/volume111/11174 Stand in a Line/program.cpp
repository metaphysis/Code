// Stand in a Line
// UVa ID: 11174
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 40005;

long long fact[MAXN];
vector<int> children[MAXN];
int sz[MAXN];
bool hasParent[MAXN];

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void dfs(int u) {
    sz[u] = 1;
    for (int v : children[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            children[i].clear();
            hasParent[i] = false;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            children[b].push_back(a);
            hasParent[a] = true;
        }
        for (int i = 1; i <= n; i++)
            if (!hasParent[i]) dfs(i);
        long long r = fact[n];
        for (int i = 1; i <= n; i++) {
            r = r * modPow(sz[i], MOD - 2) % MOD;
        }
        cout << r << "\n";
    }
    return 0;
}
