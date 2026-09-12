#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

struct Test {
    int n, k, x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, maxN = 0;
    cin >> t;
    vector<Test> tests(t);
    for (int i = 0; i < t; i++) {
        cin >> tests[i].n >> tests[i].k >> tests[i].x;
        maxN = max(maxN, tests[i].n);
    }
    vector<long long> fact(maxN + 1), invFact(maxN + 1), inv(maxN + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++)
        fact[i] = fact[i - 1] * i % mod;
    invFact[maxN] = 1;
    long long power = mod - 2;
    long long base = fact[maxN];
    while (power > 0) {
        if (power & 1)
            invFact[maxN] = invFact[maxN] * base % mod;
        base = base * base % mod;
        power >>= 1;
    }
    for (int i = maxN; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % mod;
    if (maxN >= 1)
        inv[1] = 1;
    for (int i = 2; i <= maxN; i++)
        inv[i] = mod - mod / i * inv[mod % i] % mod;
    for (int cs = 1; cs <= t; cs++) {
        int n = tests[cs - 1].n, k = tests[cs - 1].k, x = tests[cs - 1].x;
        cout << "Case " << cs << ": ";
        if (n < k * x) {
            cout << 0 << '\n';
            continue;
        }
        int m = n - k * x;
        vector<long long> pre(m + 1), cur(m + 1);
        pre[0] = 1;
        for (int box = 1; box <= k; box++) {
            cur[0] = 1;
            long long boxX = 1LL * box * x % mod;
            for (int left = 1; left <= m; left++)
                cur[left] = (box * cur[left - 1] + boxX * pre[left]) % mod * inv[box * x + left] % mod;
            pre.swap(cur);
        }
        long long ans = fact[n] * pre[m] % mod;
        long long invMin = invFact[x];
        long long minPower = 1;
        for (int i = 0; i < k; i++)
            minPower = minPower * invMin % mod;
        ans = ans * minPower % mod;
        cout << ans << '\n';
    }
    return 0;
}
