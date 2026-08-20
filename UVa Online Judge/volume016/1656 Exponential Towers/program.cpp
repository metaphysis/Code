#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int getBaseGcd(int x) {
    int res = 0, cnt, p;
    for (p = 2; p * p <= x; ++p) {
        if (x % p != 0) continue;
        cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        res = __gcd(res, cnt);
    }
    if (x > 1) res = __gcd(res, 1);
    return res;
}

void addFactor(int x, ll mul, map<int, ll>& fac) {
    int cnt, p;
    for (p = 2; p * p <= x; ++p) {
        if (x % p != 0) continue;
        cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        fac[p] += 1LL * cnt * mul;
    }
    if (x > 1) fac[x] += mul;
}

int getExpGcd(int x, const vector<int>& spf) {
    int res = 0, cnt, p;
    while (x > 1) {
        p = spf[x];
        cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        res = __gcd(res, cnt);
    }
    return res;
}

vector<int> getMobius(int n) {
    vector<int> mu(n + 1), pri;
    vector<bool> vis(n + 1, false);
    int i, p;
    mu[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!vis[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for (auto p : pri) {
            if (1LL * i * p > n) break;
            vis[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, b, c;
    char op;
    while (cin >> a >> op >> b >> op >> c) {
        map<int, ll> fac;
        int ga = getBaseGcd((int)a);
        addFactor((int)ga, 1, fac);
        addFactor((int)b, c, fac);
        vector<ll> alp;
        ll val;
        int n = 0, i, j, d, k;
        for (auto it : fac) {
            val = it.second;
            alp.push_back(val);
            n = max(n, (int)val);
        }
        vector<int> spf(n + 1), eg(n + 1), mu = getMobius(n);
        vector<ll> f(n + 1, 1);
        for (i = 2; i <= n; ++i) {
            if (spf[i] == 0) {
                for (j = i; j <= n; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
        for (i = 2; i <= n; ++i) eg[i] = getExpGcd(i, spf);
        for (i = 2; i <= n; ++i) {
            for (j = i; j <= n; j += i) f[j] += f[eg[i]];
        }
        ll ans = 0, ways, cnt;
        for (d = 2; d <= n; ++d) {
            cnt = 0;
            for (k = 1; d * k <= n; ++k) {
                if (mu[k] == 0) continue;
                ways = 1;
                for (auto val : alp) ways *= val / (d * k) + 1;
                ways -= 1;
                cnt += mu[k] * ways;
            }
            ans += cnt * (f[d] - 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
