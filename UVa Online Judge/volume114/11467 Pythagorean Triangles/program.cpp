#include <bits/stdc++.h>
using namespace std;

void add(vector<long long> &a, vector<long long> &b, vector<long long> &c, int x, int y, int k) {
    int m = max(x, y);
    a[m] += k;
    b[m] -= 1LL * k * (x + y - 2);
    c[m] += 1LL * k * (x - 1) * (y - 1);
}

vector<long long> build(int mx) {
    vector<long long> a(mx + 2), b(mx + 2), c(mx + 2), ans(mx + 2);
    for (int r = 1; r <= mx; r++)
        for (int s = 1; s <= mx; s++)
            add(a, b, c, r, s, 4);
    for (int p = 1; p <= mx; p++) {
        for (int q = 1; p + q <= mx; q++) {
            if (__gcd(p, q) != 1) continue;
            int lim = mx / max(p, q);
            for (int r = 1; r <= lim; r++) {
                for (int s = 1; s <= lim; s++) {
                    int x1 = r * p + s * q, y1 = max(r * q, s * p);
                    int x2 = max(r * p, s * q), y2 = r * q + s * p;
                    if (max(x1, y1) <= mx) add(a, b, c, x1, y1, 2);
                    if (max(x2, y2) <= mx) add(a, b, c, x2, y2, 2);
                }
            }
        }
    }
    for (int n = 1; n <= mx; n++) {
        a[n] += a[n - 1];
        b[n] += b[n - 1];
        c[n] += c[n - 1];
        ans[n] = a[n] * n * n + b[n] * n + c[n];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> nums;
    int n, mx = 0;
    while (cin >> n && n) {
        nums.push_back(n);
        mx = max(mx, n);
    }
    vector<long long> ans = build(mx);
    for (int x : nums)
        cout << ans[x] << '\n';
    return 0;
}
