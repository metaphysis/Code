#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;
const long long phi = mod - 1;

long long powerMod(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        string n;
        long long exp = 0, val, ans;
        cin >> n;
        for (char ch : n)
            exp = (exp * 10 + ch - '0') % phi;
        val = powerMod(3, exp);
        ans = (val + 1) % mod * ((mod + 1) / 2) % mod;
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
