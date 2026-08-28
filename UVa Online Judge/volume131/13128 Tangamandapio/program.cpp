#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000009LL;
int kVal;
vector<vector<int> > cmb, pats;
vector<vector<long long> > cho;

void gen(int pre, int sum, int rem, vector<int>& cur) {
    if (rem == 1) {
        pats.push_back(cur);
        return;
    }
    int x, val;
    for (x = 1; x <= pre; x++) {
        if (sum + x > kVal) break;
        val = cmb[sum + x][x];
        if (val > rem || rem % val != 0) continue;
        cur.push_back(x);
        gen(x, sum + x, rem / val, cur);
        cur.pop_back();
    }
}

long long calc(const vector<int>& cnt, const vector<int>& freq) {
    vector<int> gv, gm;
    int i, j, g, states, code, ncode, used;
    for (i = 0; i < (int)cnt.size(); i++) {
        if (i > 0 && cnt[i] == cnt[i - 1]) gm.back()++;
        else {
            gv.push_back(cnt[i]);
            gm.push_back(1);
        }
    }
    vector<int> stride(gm.size());
    states = 1;
    for (g = 0; g < (int)gm.size(); g++) {
        stride[g] = states;
        states *= gm[g] + 1;
    }
    vector<long long> dp(states), ndp(states);
    dp[0] = 1;
    for (i = 0; i < 26; i++) {
        fill(ndp.begin(), ndp.end(), 0);
        for (code = 0; code < states; code++) {
            if (dp[code] == 0) continue;
            ndp[code] = (ndp[code] + dp[code]) % mod;
            for (g = 0; g < (int)gv.size(); g++) {
                used = code / stride[g] % (gm[g] + 1);
                if (used >= gm[g] || freq[i] < gv[g]) continue;
                ncode = code + stride[g];
                ndp[ncode] = (ndp[ncode] + dp[code] * cho[freq[i]][gv[g]]) % mod;
            }
        }
        dp.swap(ndp);
    }
    code = 0;
    for (g = 0; g < (int)gm.size(); g++) code += gm[g] * stride[g];
    return dp[code];
}

void solve() {
    string s;
    int n, i, j, x;
    while (cin >> s >> kVal) {
        n = s.size();
        vector<int> freq(26, 0);
        for (i = 0; i < n; i++) freq[s[i] - 'a']++;
        if (kVal == 1) {
            long long ans = 0, pw;
            for (i = 0; i < 26; i++) {
                pw = 1;
                for (j = 0; j < freq[i]; j++) pw = pw * 2 % mod;
                ans = (ans + pw - 1 + mod) % mod;
            }
            cout << ans << '\n';
            continue;
        }
        cmb.assign(kVal + 1, vector<int>(kVal + 1, 0));
        for (i = 0; i <= kVal; i++) {
            cmb[i][0] = cmb[i][i] = 1;
            for (j = 1; j < i; j++) {
                x = cmb[i - 1][j - 1] + cmb[i - 1][j];
                cmb[i][j] = min(kVal + 1, x);
            }
        }
        cho.assign(n + 1, vector<long long>(n + 1, 0));
        for (i = 0; i <= n; i++) {
            cho[i][0] = cho[i][i] = 1;
            for (j = 1; j < i; j++) cho[i][j] = (cho[i - 1][j - 1] + cho[i - 1][j]) % mod;
        }
        pats.clear();
        vector<int> cur;
        for (i = 1; i < kVal; i++) {
            cur.push_back(i);
            gen(i, i, kVal, cur);
            cur.pop_back();
        }
        long long ans = 0;
        for (i = 0; i < (int)pats.size(); i++) ans = (ans + calc(pats[i], freq)) % mod;
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
