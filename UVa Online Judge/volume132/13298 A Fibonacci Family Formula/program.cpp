// A Fibonacci Family Formula
// UVa ID: 13298
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 1.290s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000009LL;

vector<vector<ll>> matMul(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    int n = a.size();
    vector<vector<ll>> c(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            if (a[i][k])
                for (int j = 0; j < n; ++j)
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

vector<vector<ll>> matPow(vector<vector<ll>> base, ll exp) {
    int n = base.size();
    vector<vector<ll>> res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) res = matMul(res, base);
        base = matMul(base, base);
        exp >>= 1;
    }
    return res;
}

ll solve(int k, ll n) {
    if (n < k) {
        if (n == 0 || n == 1) return 1;
        ll ans = 1;
        for (int i = 0; i < n - 1; ++i) ans = ans * 2 % MOD;
        return ans;
    }

    vector<ll> init(k);
    for (int i = 0; i < k; ++i) {
        int idx = k - 1 - i;
        if (idx == 0 || idx == 1) init[i] = 1;
        else {
            ll val = 1;
            for (int j = 0; j < idx - 1; ++j) val = val * 2 % MOD;
            init[i] = val;
        }
    }

    vector<vector<ll>> A(k, vector<ll>(k, 0));
    for (int j = 0; j < k; ++j) A[0][j] = 1;
    for (int i = 1; i < k; ++i) A[i][i-1] = 1;

    ll exp = n - (k - 1);
    vector<vector<ll>> P = matPow(A, exp);

    ll ans = 0;
    for (int j = 0; j < k; ++j)
        ans = (ans + P[0][j] * init[j]) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    ll n;
    while (cin >> k >> n) {
        if (k == 0 && n == 0) break;
        cout << solve(k, n) << '\n';
    }
    return 0;
}
