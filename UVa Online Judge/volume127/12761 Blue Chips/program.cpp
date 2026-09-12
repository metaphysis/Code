#include <bits/stdc++.h>
using namespace std;

vector<int> mulPoly(const vector<int>& a, const vector<int>& b, int n) {
    vector<int> c(n, 0);
    int i, j, pos;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            pos = (i + j) % n;
            c[pos] = (c[pos] + (long long)a[i] * b[j]) % n;
        }
    }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, d, i, best, w;
    long long k;
    cin >> t;
    while (t--) {
        cin >> n >> k >> d;
        vector<int> x(n), base(n, 0), ans(n, 0), win;
        for (i = 0; i < n; i++) cin >> x[i];
        for (i = 1; i <= d; i++) {
            base[i] = (base[i] + 1) % n;
            if (i != n - i) base[n - i] = (base[n - i] + 1) % n;
        }
        ans[0] = 1;
        while (k > 0) {
            if (k & 1) ans = mulPoly(ans, base, n);
            base = mulPoly(base, base, n);
            k >>= 1;
        }
        x = mulPoly(ans, x, n);
        best = *min_element(x.begin(), x.end());
        for (i = 0; i < n; i++) if (x[i] == best) win.push_back(i + 1);
        cout << best << '\n';
        for (w = 0; w < (int)win.size(); w++) cout << (w ? " " : "") << win[w];
        cout << '\n';
    }
    return 0;
}
