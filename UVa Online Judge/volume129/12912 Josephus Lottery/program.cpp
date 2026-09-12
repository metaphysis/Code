#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k && (n || k)) {
        int m, q, pos = 0;
        for (m = 2; m <= n; ++m) {
            q = (k - 1) % m;
            if (pos == 0) pos = (q + 1) % m;
            else pos = (q - pos + m) % m;
        }
        cout << pos + 1 << '\n';
    }
    return 0;
}
