#include <bits/stdc++.h>
using namespace std;

const long long mod = 1711276033LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> nums;
    int n, maxN = 0;
    while (cin >> n) {
        nums.push_back(n);
        maxN = max(maxN, n);
    }
    vector<long long> fact(maxN + 1), inv(maxN + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; ++i)
        fact[i] = fact[i - 1] * i % mod;
    if (maxN >= 1)
        inv[1] = 1;
    for (int i = 2; i <= maxN; ++i)
        inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;
    for (int index = 0; index < static_cast<int>(nums.size()); ++index) {
        n = nums[index];
        for (int m = 1; m <= n; ++m) {
            long long tri = 1LL * m * (m + 1) / 2 % mod;
            long long ans = fact[n] * tri % mod * inv[n - m + 1] % mod;
            if (m > 1)
                cout << ' ';
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}
