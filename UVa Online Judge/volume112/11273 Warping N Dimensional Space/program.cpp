#include <bits/stdc++.h>
using namespace std;

int main() {
    const int mod = 4000039;
    vector<int> nums;
    int n, maxN = 0;
    while (cin >> n) {
        nums.push_back(n);
        if (n > maxN) maxN = n;
    }
    vector<int> phi(maxN + 1);
    vector<long long> ans(maxN + 1);
    for (int i = 0; i <= maxN; i++) phi[i] = i;
    for (int i = 2; i <= maxN; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= maxN; j += i) phi[j] -= phi[j] / i;
        }
    }
    ans[0] = 1;
    for (int i = 1; i <= maxN; i++) ans[i] = ans[i - 1] * phi[i] % mod;
    for (int x : nums) cout << ans[x] << '\n';
    return 0;
}
