
// Random Number
// UVa ID: 504
// Verdict: Accepted
// Submission Date: 2026-06-15
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static const int BASE = 10000;
    vector<int> d;
    BigInt(unsigned long long x = 0) { while (x) { d.push_back(x % BASE); x /= BASE; } if (d.empty()) d.push_back(0); }
    BigInt& operator+=(const BigInt& b) {
        int carry = 0;
        for (size_t i = 0; i < d.size() || i < b.d.size() || carry; ++i) {
            if (i < d.size()) carry += d[i];
            if (i < b.d.size()) carry += b.d[i];
            if (i < d.size()) d[i] = carry % BASE;
            else d.push_back(carry % BASE);
            carry /= BASE;
        }
        return *this;
    }
    BigInt operator+(const BigInt& b) const { BigInt r = *this; r += b; return r; }
    BigInt& operator-=(const BigInt& b) {
        int borrow = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            int sub = (i < b.d.size()) ? b.d[i] : 0;
            d[i] -= sub + borrow;
            if (d[i] < 0) d[i] += BASE, borrow = 1;
            else borrow = 0;
        }
        while (d.size() > 1 && d.back() == 0) d.pop_back();
        return *this;
    }
    BigInt operator-(const BigInt& b) const { BigInt r = *this; r -= b; return r; }
    BigInt operator/(unsigned long long div) const {
        BigInt r;
        unsigned long long rem = 0;
        for (int i = d.size() - 1; i >= 0; --i) {
            rem = rem * BASE + d[i];
            r.d.push_back(rem / div);
            rem %= div;
        }
        reverse(r.d.begin(), r.d.end());
        while (r.d.size() > 1 && r.d.back() == 0) r.d.pop_back();
        return r;
    }
    int cmp(const BigInt& b) const {
        if (d.size() != b.d.size()) return d.size() < b.d.size() ? -1 : 1;
        for (int i = d.size() - 1; i >= 0; --i) if (d[i] != b.d[i]) return d[i] < b.d[i] ? -1 : 1;
        return 0;
    }
    bool operator>(const BigInt& b) const { return cmp(b) > 0; }
    bool isZero() const { return d.size() == 1 && d[0] == 0; }
    unsigned long long toULL() const {
        unsigned long long r = 0;
        for (int i = d.size() - 1; i >= 0; --i) r = r * BASE + d[i];
        return r;
    }
};

int M, N;
vector<vector<BigInt>> dp;

void computeDP() {
    dp.assign(N + 2, vector<BigInt>(M + 2));
    for (int last = 1; last <= M; ++last) 
        dp[N][last] = (last >= N) ? BigInt(1) : BigInt(0);
    for (int pos = N - 1; pos >= 1; --pos) {
        BigInt suffix(0);
        for (int last = M; last >= 1; --last) {
            suffix = suffix + dp[pos + 1][last];
            dp[pos][last] = (last >= pos) ? suffix : BigInt(0);
        }
    }
}

BigInt G(BigInt A, BigInt B, const string& bits, int idx) {
    if (idx >= (int)bits.size() || A.cmp(B) == 0) return A;
    BigInt mid = (A + B) / 2ULL;
    return bits[idx] == '0' ? G(A, mid, bits, idx + 1) : G(mid + 1ULL, B, bits, idx + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K; cin >> K;
    for (int ds = 0; ds < K; ++ds) {
        if (ds) cout << '\n';
        cin >> M >> N;
        string bin; cin >> bin;
        bin = bin.substr(2);
        computeDP();
        BigInt total(0);
        for (int v = 1; v <= M; ++v) total = total + dp[1][v];
        BigInt target = G(BigInt(1), total, bin, 0);
        vector<int> seq(N);
        int last = 1;
        BigInt remain = target;
        for (int pos = 1; pos <= N; ++pos) {
            for (int v = last; v <= M; ++v) {
                if (v < pos) continue;
                BigInt cnt = dp[pos][v];
                if (cnt.isZero()) continue;
                if (remain > cnt) remain = remain - cnt;
                else { seq[pos - 1] = v; last = v; break; }
            }
        }
        for (int i = 0; i < N; ++i) {
            if (i && i % 20 == 0) cout << '\n';
            if (i % 20) cout << ' ';
            cout << setw(3) << seq[i];
        }
        cout << '\n';
    }
    return 0;
}
