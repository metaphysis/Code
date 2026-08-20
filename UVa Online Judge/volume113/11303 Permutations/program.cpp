// Permutations
// UVa ID: 11303
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

class BigInt {
    static const int BASE = 1000000000;
    vector<int> d;
public:
    BigInt() : d(1, 0) {}
    BigInt(long long x) { fromInt(x); }
    BigInt(const string& s) { fromString(s); }
    void fromInt(long long x) {
        d.clear();
        if (x == 0) { d.push_back(0); return; }
        while (x > 0) { d.push_back(x % BASE); x /= BASE; }
    }
    void fromString(const string& s) {
        d.clear();
        d.push_back(0);
        for (char c : s) {
            if (c < '0' || c > '9') continue;
            multiplySmall(10);
            addSmall(c - '0');
        }
    }
    void addSmall(int x) {
        int carry = x;
        for (int i = 0; carry; ++i) {
            if (i == (int)d.size()) d.push_back(0);
            long long v = (long long)d[i] + carry;
            d[i] = v % BASE;
            carry = v / BASE;
        }
    }
    void multiplySmall(int x) {
        if (x == 0) { d.clear(); d.push_back(0); return; }
        if (x == 1) return;
        long long carry = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            long long cur = (long long)d[i] * x + carry;
            d[i] = cur % BASE;
            carry = cur / BASE;
        }
        while (carry > 0) { d.push_back(carry % BASE); carry /= BASE; }
    }
    int compare(const BigInt& other) const {
        if (d.size() != other.d.size())
            return d.size() > other.d.size() ? 1 : -1;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i])
                return d[i] > other.d[i] ? 1 : -1;
        }
        return 0;
    }
    bool operator>(const BigInt& other) const {
        return compare(other) > 0;
    }
    BigInt& operator-=(const BigInt& other) {
        long long borrow = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            long long sub = borrow + (i < (int)other.d.size() ? other.d[i] : 0);
            long long cur = (long long)d[i] - sub;
            if (cur < 0) { cur += BASE; borrow = 1; }
            else borrow = 0;
            d[i] = (int)cur;
        }
        while (d.size() > 1 && d.back() == 0) d.pop_back();
        return *this;
    }
    BigInt& operator*=(int x) { multiplySmall(x); return *this; }
};

const int MAXN = 250;
vector<vector<BigInt>> ways(MAXN + 1, vector<BigInt>(MAXN + 1));

// ways[r][t] = r! / t!
void buildWays() {
    for (int r = 0; r <= MAXN; ++r) {
        ways[r][r] = BigInt(1);
        for (int t = r - 1; t >= 0; --t) {
            ways[r][t] = ways[r][t + 1];
            ways[r][t] *= (t + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildWays();
    int n, m;
    string Kstr;
    while (cin >> n >> m >> Kstr) {
        vector<int> S(m);
        for (int i = 0; i < m; ++i) cin >> S[i];
        vector<int> posInS(n + 1, -1);
        for (int i = 0; i < m; ++i) posInS[S[i]] = i;
        BigInt K(Kstr);
        vector<bool> used(n + 1, false);
        vector<int> ans;
        ans.reserve(n);
        int q = 0;
        for (int pos = 0; pos < n; ++pos) {
            int r = n - pos;
            for (int x = 1; x <= n; ++x) {
                if (used[x]) continue;
                int p = posInS[x];
                if (p != -1 && p != q) continue;
                int newQ = q + (p == q ? 1 : 0);
                int rPrime = r - 1;
                int tPrime = m - newQ;
                const BigInt& cnt = ways[rPrime][tPrime];
                if (K > cnt) { K -= cnt; continue; }
                ans.push_back(x);
                used[x] = true;
                q = newQ;
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
