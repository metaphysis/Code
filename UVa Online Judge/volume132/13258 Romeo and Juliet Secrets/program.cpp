#include <bits/stdc++.h>
using namespace std;

vector<int> getZ(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    while (testCase--) {
        string t, w;
        int k;
        cin >> t >> w >> k;
        int n = t.size(), m = w.size(), ans = 0;
        string s1 = w + "{" + t;
        vector<int> z1 = getZ(s1);
        string rt = t, rw = w;
        reverse(rt.begin(), rt.end());
        reverse(rw.begin(), rw.end());
        string s2 = rw + "{" + rt;
        vector<int> z2 = getZ(s2);
        for (int i = 0; i + m <= n; i++) {
            int pre = min(m, z1[m + 1 + i]);
            int suf = min(m, z2[n - i + 1]);
            if (pre + suf + k >= m) ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
