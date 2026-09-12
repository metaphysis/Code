#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n, k, a, b, ans;
        cin >> n >> k;
        a = k + 1;
        b = a * a * a - k * k * k;
        ans = (n - k + 1) * b + k * k * k;
        cout << ans << '\n';
    }
    return 0;
}
