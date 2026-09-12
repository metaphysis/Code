#include <bits/stdc++.h>
using namespace std;

const int maxN = 1000000;
const int primeCnt = 15;
int base[primeCnt] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
vector<int> mu, pri, sq;
vector<unsigned short> fac;
vector<bool> vis;

void init() {
    mu.assign(maxN + 1, 0);
    fac.assign(maxN + 1, 0);
    vis.assign(maxN + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= maxN; i++) {
        if (!vis[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; j < (int)pri.size() && i * pri[j] <= maxN; j++) {
            int v = i * pri[j];
            vis[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                break;
            } else {
                mu[v] = -mu[i];
            }
        }
    }
    sq.push_back(1);
    for (int i = 2; i <= maxN; i++)
        if (mu[i] != 0) sq.push_back(i);
    for (int i = 0; i < primeCnt; i++)
        for (int j = base[i]; j <= maxN; j += base[i])
            fac[j] |= (1 << i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t, r1, c1, r2, c2, n, p, ban, lim;
    long long total, good, a, b;
    cin >> t;
    while (t--) {
        cin >> r1 >> c1 >> r2 >> c2;
        cin >> n;
        ban = 0;
        for (int i = 0; i < n; i++) {
            cin >> p;
            for (int j = 0; j < primeCnt; j++)
                if (base[j] == p) ban |= (1 << j);
        }
        lim = min(r2, c2);
        good = 0;
        for (int x : sq) {
            if (x > lim) break;
            if (fac[x] & ban) continue;
            a = r2 / x - (r1 - 1) / x;
            b = c2 / x - (c1 - 1) / x;
            good += 1LL * mu[x] * a * b;
        }
        total = 1LL * (r2 - r1 + 1) * (c2 - c1 + 1);
        cout << total - good << '\n';
    }
    return 0;
}
