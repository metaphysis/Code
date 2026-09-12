#include <bits/stdc++.h>
using namespace std;

const int mod = 342307123;
vector<pair<int, int> > sta;
int toD[6], toR[6];

int getVal(int mask, int code) {
    return __builtin_parity(mask & code);
}

void buildSta() {
    map<int, int> id;
    sta.push_back({1, 2});
    id[6] = 0;
    for (int i = 0; i < (int)sta.size(); i++) {
        int x = sta[i].first, y = sta[i].second;
        int a = x * 4 + (x ^ y), b = (x ^ y) * 4 + y;
        if (!id.count(a)) {
            id[a] = sta.size();
            sta.push_back({x, x ^ y});
        }
        if (!id.count(b)) {
            id[b] = sta.size();
            sta.push_back({x ^ y, y});
        }
        toD[i] = id[a];
        toR[i] = id[b];
    }
}

int getPart(const string &path, int code, const vector<array<array<int, 4>, 6> > &cnt) {
    int state = 0, ans = 0, h = path.size();
    for (int i = 0; i < h; i++) {
        if (path[i] == 'D') state = toD[state];
        else {
            ans += cnt[h - i - 1][toD[state]][code];
            if (ans >= mod) ans -= mod;
            state = toR[state];
        }
    }
    ans += cnt[0][state][code];
    if (ans >= mod) ans -= mod;
    return ans;
}

int getRank(const string &path) {
    int ans = 0;
    for (char ch : path) ans = ((long long)ans * 2 + (ch == 'R')) % mod;
    return ans;
}

int getFull(int p, const vector<array<int, 4> > &pre, const vector<array<array<int, 4>, 6> > &cnt) {
    long long ans = 0;
    for (int code = 0; code < 4; code++) ans = (ans + (long long)pre[p][code] * cnt.back()[0][code]) % mod;
    return ans;
}

int getPref(int p, const string &path, const string &s, const vector<array<int, 4> > &pre, const vector<array<array<int, 4>, 6> > &cnt) {
    int ans = getFull(p, pre, cnt), n = s.size();
    if (p == n - 1) {
        ans += s[p] - '0';
        if (ans >= mod) ans -= mod;
    } else {
        int code = (s[p] - '0') | ((s[p + 1] - '0') << 1);
        ans += getPart(path, code, cnt);
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

int getPoint(int p, const string &path, const string &s) {
    if (p == (int)s.size() - 1) return s[p] - '0';
    int state = 0, code = (s[p] - '0') | ((s[p + 1] - '0') << 1);
    for (char ch : path) {
        if (ch == 'D') state = toD[state];
        else state = toR[state];
    }
    return getVal(sta[state].first, code);
}

void readPos(int &p, string &path) {
    string line;
    getline(cin, line);
    while (line.empty()) getline(cin, line);
    stringstream ss(line);
    ss >> p;
    path.clear();
    ss >> path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildSta();
    int tc;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        string s, ta, tb;
        int g, pa, pb, h;
        cin >> s >> g;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        readPos(pa, ta);
        readPos(pb, tb);
        h = g - 1;
        vector<array<array<int, 4>, 6> > cnt(h + 1);
        for (int state = 0; state < 6; state++)
            for (int code = 0; code < 4; code++)
                cnt[0][state][code] = getVal(sta[state].first, code);
        for (int len = 1; len <= h; len++)
            for (int state = 0; state < 6; state++)
                for (int code = 0; code < 4; code++)
                    cnt[len][state][code] = (cnt[len - 1][toD[state]][code] + cnt[len - 1][toR[state]][code]) % mod;
        int n = s.size();
        vector<array<int, 4> > pre(n);
        for (int i = 0; i + 1 < n; i++) {
            pre[i + 1] = pre[i];
            int code = (s[i] - '0') | ((s[i + 1] - '0') << 1);
            pre[i + 1][code]++;
        }
        int oneA = getPref(pa, ta, s, pre, cnt), oneB = getPref(pb, tb, s, pre, cnt);
        int ones = (oneB - oneA + getPoint(pa, ta, s)) % mod;
        if (ones < 0) ones += mod;
        int pow2 = 1;
        for (int i = 0; i < h; i++) pow2 = (long long)pow2 * 2 % mod;
        int rankA = getRank(ta), rankB = getRank(tb);
        int len = ((long long)(pb - pa) * pow2 + rankB - rankA + 1) % mod;
        if (len < 0) len += mod;
        int zeros = len - ones;
        if (zeros < 0) zeros += mod;
        cout << "Case " << cs << ": " << zeros << ' ' << ones << '\n';
    }
    return 0;
}
