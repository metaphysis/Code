// Top Secret
// UVa ID: 12183
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 1.400s

#include <bits/stdc++.h>
using namespace std;

// 循环矩阵乘法：返回两个循环矩阵第一行的卷积
vector<long long> multiplyMatrix(const vector<long long>& a, const vector<long long>& b, long long mod) {
    int n = (int)a.size();
    vector<long long> c(n, 0);
    for (int k = 0; k < n; ++k) {
        long long sum = 0;
        for (int i = 0; i < n; ++i)
            sum = (sum + a[i] * b[(k - i + n) % n]) % mod;
        c[k] = sum;
    }
    return c;
}

// 循环矩阵作用于向量
vector<long long> applyMatrix(const vector<long long>& a, const vector<long long>& v, long long mod) {
    int n = (int)a.size();
    vector<long long> res(n, 0);
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int t = 0; t < n; ++t)
            sum = (sum + a[t] * v[(i + t) % n]) % mod;
        res[i] = sum;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, S, L, R, X;
        cin >> N >> S >> L >> R >> X;

        long long mod = 1;
        for (int i = 0; i < X; ++i) mod *= 10;

        vector<long long> v(N);
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
            v[i] %= mod;
        }

        // 单位矩阵的第一行
        vector<long long> power(N, 0);
        power[0] = 1;

        // 变换矩阵 M 的第一行
        vector<long long> base(N, 0);
        base[0] = 1;
        base[1] = R % mod;
        base[N - 1] = L % mod;

        long long s = S;
        while (s) {
            if (s & 1) power = multiplyMatrix(power, base, mod);
            base = multiplyMatrix(base, base, mod);
            s >>= 1;
        }

        vector<long long> result = applyMatrix(power, v, mod);

        for (int i = 0; i < N; ++i) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << '\n';
    }

    return 0;
}
