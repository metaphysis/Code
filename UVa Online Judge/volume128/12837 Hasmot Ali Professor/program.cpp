#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct Key {
    ull a, b;
    bool operator == (const Key &other) const {
        return a == other.a && b == other.b;
    }
};

struct Hash {
    size_t operator () (const Key &key) const {
        return key.a ^ (key.b + 0x9e3779b97f4a7c15ULL + (key.a << 6) + (key.a >> 2));
    }
};

ull getCode(const string &s) {
    ull val = 0;
    for (char c : s)
        val = (val << 5) | (c - 'a' + 1);
    return val | ((ull)s.size() << 50);
}

vector<int> getSa(const string &s) {
    int n = s.size(), step = 1;
    vector<int> sa(n), rk(n), tmp(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rk[i] = s[i] - 'a';
    }
    while (step < n) {
        sort(sa.begin(), sa.end(), [&](int x, int y) {
            if (rk[x] != rk[y]) return rk[x] < rk[y];
            int a = x + step < n ? rk[x + step] : -1;
            int b = y + step < n ? rk[y + step] : -1;
            return a < b;
        });
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            int x = sa[i - 1], y = sa[i];
            int ax = x + step < n ? rk[x + step] : -1;
            int ay = y + step < n ? rk[y + step] : -1;
            if (rk[x] != rk[y] || ax != ay) tmp[y] = tmp[x] + 1;
            else tmp[y] = tmp[x];
        }
        rk = tmp;
        if (rk[sa[n - 1]] == n - 1) break;
        step <<= 1;
    }
    return sa;
}

vector<int> getLcp(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n);
    for (int i = 1; i < n; i++) {
        int x = sa[i - 1], y = sa[i], len = 0;
        while (x + len < n && y + len < n && s[x + len] == s[y + len]) len++;
        lcp[i] = len;
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        string s;
        int q, n;
        cin >> s >> q;
        n = s.size();
        unordered_map<Key, int, Hash> id;
        vector<int> ask(q);
        vector<long long> ans;
        for (int i = 0; i < q; i++) {
            string x, y;
            ull a, b;
            cin >> x >> y;
            a = getCode(x);
            b = getCode(y);
            Key key = {a, b};
            auto it = id.find(key);
            if (it == id.end()) {
                int now = ans.size();
                id[key] = now;
                ans.push_back(0);
                ask[i] = now;
            } else ask[i] = it->second;
        }
        vector<array<ull, 11> > code(n);
        for (int i = 0; i < n; i++) {
            ull val = 0;
            for (int len = 1; len <= 10 && i + len <= n; len++) {
                val = (val << 5) | (s[i + len - 1] - 'a' + 1);
                code[i][len] = val | ((ull)len << 50);
            }
        }
        vector<int> sa = getSa(s);
        vector<int> lcp = getLcp(s, sa);
        for (int i = 0; i < n; i++) {
            int pos = sa[i], low = lcp[i] + 1, high = n - pos;
            for (int len = low; len <= high; len++) {
                int lim = min(10, len);
                for (int px = 1; px <= lim; px++) {
                    ull a = code[pos][px];
                    for (int sy = 1; sy <= lim; sy++) {
                        ull b = code[pos + len - sy][sy];
                        Key key = {a, b};
                        auto it = id.find(key);
                        if (it != id.end()) ans[it->second]++;
                    }
                }
            }
        }
        cout << "Case " << tc << ":\n";
        for (int i = 0; i < q; i++)
            cout << ans[ask[i]] << '\n';
    }
    return 0;
}
