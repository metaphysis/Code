#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;

int getCode(const vector<int> &val, const vector<int> &rad) {
    int code = 0, base = 1;
    for (int i = 0; i < (int)val.size(); i++) {
        code += val[i] * base;
        base *= rad[i];
    }
    return code;
}

int solve() {
    int n;
    cin >> n;
    vector<int> a(n), prm;
    for (int &x : a)
        cin >> x;
    for (int x = 2; x <= 19; x++) {
        bool ok = true;
        for (int y = 2; y * y <= x; y++)
            if (x % y == 0) {
                ok = false;
                break;
            }
        if (ok)
            prm.push_back(x);
    }
    int pNum = prm.size();
    vector<vector<int> > fac(n, vector<int>(pNum, 0));
    vector<int> big(n, 0), lim(pNum, 0);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        for (int j = 0; j < pNum; j++) {
            while (x % prm[j] == 0) {
                fac[i][j]++;
                x /= prm[j];
            }
            lim[j] = max(lim[j], fac[i][j]);
        }
        big[i] = x;
    }
    vector<int> rad(pNum);
    int stNum = 1;
    for (int i = 0; i < pNum; i++) {
        rad[i] = lim[i] + 1;
        stNum *= rad[i];
    }
    vector<vector<int> > nxt(n, vector<int>(stNum));
    vector<vector<int> > mul(n, vector<int>(stNum));
    for (int k = 0; k < n; k++) {
        for (int s = 0; s < stNum; s++) {
            int tmp = s, ns = 0, base = 1, val = 1;
            for (int j = 0; j < pNum; j++) {
                int old = tmp % rad[j];
                tmp /= rad[j];
                int now = max(old, fac[k][j]);
                ns += now * base;
                base *= rad[j];
                for (int z = old; z < now; z++)
                    val = val * prm[j] % mod;
            }
            nxt[k][s] = ns;
            mul[k][s] = val;
        }
    }
    map<int, vector<int> > grp;
    for (int i = 0; i < n; i++)
        grp[big[i]].push_back(i);
    vector<int> dp(stNum, 0), ndp(stNum, 0), no(stNum, 0), yes(stNum, 0), nn(stNum, 0), yy(stNum, 0);
    dp[0] = 1;
    for (auto &g : grp) {
        if (g.first == 1) {
            for (int id : g.second) {
                ndp = dp;
                for (int s = 0; s < stNum; s++)
                    ndp[nxt[id][s]] = (ndp[nxt[id][s]] + (long long)dp[s] * mul[id][s]) % mod;
                dp.swap(ndp);
            }
        } else {
            no = dp;
            fill(yes.begin(), yes.end(), 0);
            for (int id : g.second) {
                fill(nn.begin(), nn.end(), 0);
                fill(yy.begin(), yy.end(), 0);
                for (int s = 0; s < stNum; s++) {
                    nn[s] = (nn[s] + no[s]) % mod;
                    yy[s] = (yy[s] + yes[s]) % mod;
                    int ns = nxt[id][s], mlt = mul[id][s];
                    yy[ns] = (yy[ns] + (long long)no[s] * mlt % mod * g.first) % mod;
                    yy[ns] = (yy[ns] + (long long)yes[s] * mlt) % mod;
                }
                no.swap(nn);
                yes.swap(yy);
            }
            for (int s = 0; s < stNum; s++)
                dp[s] = (no[s] + yes[s]) % mod;
        }
    }
    int ans = 0;
    for (int x : dp)
        ans = (ans + x) % mod;
    return (ans - 1 + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++)
        cout << "Case " << cs << ": " << solve() << '\n';
    return 0;
}
