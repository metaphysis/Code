#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, a, b;
    long long p, value, prod;
    while (cin >> n >> p) {
        vector<long long> val(n + 1), pre(n + 1), invPre(n + 1);
        vector<int> zero(n + 1);
        pre[0] = 1;
        for (int i = 1; i <= n; ++i) {
            cin >> value;
            val[i] = (modPow(p, value) + 1) % mod;
            pre[i] = pre[i - 1];
            zero[i] = zero[i - 1];
            if (val[i] == 0) {
                ++zero[i];
                val[i] = 1;
            }
            pre[i] = pre[i] * val[i] % mod;
        }
        invPre[n] = modPow(pre[n], mod - 2);
        for (int i = n; i >= 1; --i) invPre[i - 1] = invPre[i] * val[i] % mod;
        cin >> q;
        while (q--) {
            cin >> a >> b;
            if (zero[b] - zero[a - 1] > 0) prod = 0;
            else prod = pre[b] * invPre[a - 1] % mod;
            cout << (prod + mod - 1) % mod << '\n';
        }
    }
    return 0;
}
