#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

struct Query {
    int n, a, b;
};

void initData(int maxN, vector<long long>& euler, vector<long long>& inv) {
    vector<long long> comb(maxN + 1, 0);
    euler.assign(maxN + 1, 0);
    inv.assign(maxN + 2, 0);
    comb[0] = euler[0] = 1;
    inv[1] = 1;
    for (int i = 2; i <= maxN + 1; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int len = 1; len <= maxN; len++) {
        for (int k = len; k >= 1; k--) comb[k] = (comb[k] + comb[k - 1]) % mod;
        if (len % 2 == 1) continue;
        long long sum = 0;
        for (int k = 2; k <= len; k += 2) {
            long long term = comb[k] * euler[len - k] % mod;
            if (k % 4 == 2) sum = (sum + term) % mod;
            else sum = (sum - term + mod) % mod;
        }
        euler[len] = sum;
    }
}

long long solveQuery(int n, int a, int b, const vector<long long>& euler, const vector<long long>& inv) {
    if (a == b) return 0;
    if (a > b) swap(a, b);
    int p = a - 1, r = n - b, total = n - 2, s = p + r;
    long long ans = 0, prev = 0, cur = 1;
    for (int k = 0; k <= s; k++) {
        if (k % 2 == n % 2) {
            long long term = cur * euler[total - k] % mod;
            if ((k / 2) % 2 == 0) ans = (ans + term) % mod;
            else ans = (ans - term + mod) % mod;
        }
        if (k == s) break;
        if (n % 2 == 1) cur = cur * (s - k) % mod * inv[k + 1] % mod;
        else {
            long long next = ((p - r) * cur + (k - 1 - s) * prev) % mod;
            next = (next + mod) % mod * inv[k + 1] % mod;
            prev = cur;
            cur = next;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Query> queries;
    vector<long long> euler, inv;
    int n, a, b, maxN = 0;
    while (cin >> n >> a >> b) {
        queries.push_back({n, a, b});
        maxN = max(maxN, n - 2);
    }
    initData(maxN, euler, inv);
    for (const auto& query : queries) cout << solveQuery(query.n, query.a, query.b, euler, inv) << '\n';
    return 0;
}
