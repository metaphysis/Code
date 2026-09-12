#include <bits/stdc++.h>
using namespace std;

const long long Mod = 1000000007;
long long mat[105][105];

long long modPow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int getRank(int n, long long p) {
    int row = 0;
    for (int col = 0; col < n && row < n; col++) {
        int sel = -1;
        for (int i = row; i < n; i++) if (sel == -1 && mat[i][col]) sel = i;
        if (sel == -1) continue;
        for (int j = col; j < n; j++) swap(mat[row][j], mat[sel][j]);
        long long inv = modPow(mat[row][col], p - 2, p);
        for (int j = col; j < n; j++) mat[row][j] = mat[row][j] * inv % p;
        for (int i = 0; i < n; i++) if (i != row && mat[i][col]) {
            long long mul = mat[i][col];
            for (int j = col; j < n; j++) mat[i][j] = (mat[i][j] - mul * mat[row][j] % p + p) % p;
        }
        row++;
    }
    return row;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, m;
        long long p;
        cin >> n >> m >> p;
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < n; i++) mat[i][i] = 1;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            mat[u][v] = p - 1;
            mat[v][u] = p - 1;
        }
        int rank = getRank(n, p);
        long long ans = modPow(p % Mod, n - rank, Mod);
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
