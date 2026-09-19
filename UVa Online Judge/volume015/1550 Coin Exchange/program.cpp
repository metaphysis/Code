#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a1, a2;
    while (cin >> a1 >> a2) {
        if (a1 == 0 && a2 == 0) break;
        long long g = a1 * a2 - a1 - a2, n = (a1 - 1) * (a2 - 1) / 2;
        cout << max(g, 0LL) << ' ' << n << '\n';
    }
    return 0;
}
