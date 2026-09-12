#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d, n;
    while (cin >> d >> n && (d || n)) {
        int m = n - 4;
        vector<long long> p(5), ans(n + 1);
        p[0] = 3LL * d * d * d * d;
        p[1] = -12LL * d * d * d;
        p[2] = -48LL * d * d;
        p[3] = -16LL * d;
        p[4] = 16;
        for (int i = 0; i <= 4; i++) ans[i] = p[i];
        if (m > 0) {
            for (int i = 0; i <= 4; i++) ans[i + m] += p[i];
        }
        for (int i = n; i >= 0; i--) {
            if (i < n) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
