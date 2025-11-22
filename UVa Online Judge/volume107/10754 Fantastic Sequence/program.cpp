// Fantastic Sequence
// UVa ID: 10754
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

mat multiply(const mat &A, const mat &B, ll mod) {
    int n = A.size(), m = B[0].size(), p = B.size();
    mat C(n, vec(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}

mat power(mat A, ll exp, ll mod) {
    int n = A.size();
    mat result(n, vec(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) result = multiply(result, A, mod);
        A = multiply(A, A, mod);
        exp >>= 1;
    }
    return result;
}

ll solve() {
    int k;
    ll m, n;
    cin >> k >> m >> n;
    vector<ll> c(k + 1), a(k);
    for (int i = 0; i <= k; i++) cin >> c[i];
    for (int i = 0; i < k; i++) cin >> a[i];
    
    if (n < k) return (a[n] % m + m) % m;
    
    if (k == 0) {
        ll val = c[0] % m;
        return (val + m) % m;
    }
    
    mat M(k + 1, vec(k + 1, 0));
    M[0][0] = c[0] % m;
    for (int i = 1; i < k; i++) M[0][i] = c[i] % m;
    M[0][k] = c[k] % m;
    for (int i = 1; i < k; i++) M[i][i - 1] = 1;
    M[k][k] = 1;
    
    mat init(k + 1, vec(1));
    for (int i = 0; i < k; i++) init[i][0] = a[k - 1 - i] % m;
    init[k][0] = 1;
    
    mat Mn = power(M, n - k + 1, m);
    mat res = multiply(Mn, init, m);
    ll ans = res[0][0] % m;
    return (ans + m) % m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    bool first = true;
    while (t--) {
        if (!first) cout << "\n";
        first = false;
        cout << solve() << '\n';
    }
    return 0;
}
