// The Curse of Barbosa
// UVa ID: 10839
// Verdict: Accepted
// Submission Date: 2026-01-15
// UVa Run Time: 0.340s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int BASE = 10000;
struct BigInt {
    vector<int> d;
    BigInt(long long x = 0) {
        if (!x) d.push_back(0);
        while (x) d.push_back(x % BASE), x /= BASE;
    }
    BigInt operator+(const BigInt& b) const {
        BigInt r;
        r.d.clear();
        int carry = 0, sz = max(d.size(), b.d.size());
        for (int i = 0; i < sz || carry; ++i) {
            int sum = carry;
            if (i < d.size()) sum += d[i];
            if (i < b.d.size()) sum += b.d[i];
            r.d.push_back(sum % BASE);
            carry = sum / BASE;
        }
        while (r.d.size() > 1 && !r.d.back()) r.d.pop_back();
        return r;
    }
    BigInt operator*(long long x) const {
        BigInt r;
        r.d.resize(d.size() + 10, 0);
        long long carry = 0;
        for (int i = 0; i < d.size() || carry; ++i) {
            long long sum = carry;
            if (i < d.size()) sum += 1LL * d[i] * x;
            r.d[i] = sum % BASE;
            carry = sum / BASE;
        }
        while (r.d.size() > 1 && !r.d.back()) r.d.pop_back();
        return r;
    }
    BigInt operator/(long long x) const {
        BigInt r;
        r.d.clear();
        vector<int> tmp = d;
        reverse(tmp.begin(), tmp.end());
        long long rr = 0;
        for (int v : tmp) {
            rr = rr * BASE + v;
            r.d.push_back(rr / x);
            rr %= x;
        }
        reverse(r.d.begin(), r.d.end());
        while (r.d.size() > 1 && !r.d.back()) r.d.pop_back();
        return r;
    }
    friend ostream& operator<<(ostream& os, const BigInt& b) {
        os << b.d.back();
        for (int i = b.d.size() - 2; i >= 0; --i)
            os << setw(4) << setfill('0') << b.d[i];
        return os;
    }
};

const int MAX = 35;
BigInt dp[MAX][MAX][MAX];
bool visited[MAX][MAX][MAX];

BigInt dfs(int a, int b, int c) {
    if (a == 0 && b == 0 && c == 0) return BigInt(0);
    if (visited[a][b][c]) return dp[a][b][c];
    if (a == 1) {
        if (b == 0 && c == 0) return dp[a][b][c] = BigInt(0);
        if (b == c) return dp[a][b][c] = BigInt(2);
        if (abs(b - c) == 1) return dp[a][b][c] = BigInt(1);
        return dp[a][b][c] = BigInt(0);
    }
    visited[a][b][c] = true;
    BigInt r(0);
    for (int i = 1; b - i >= 0 && c - i >= 0; ++i)
        r = r + dfs(a - 1, b - i, c - i) * 2;
    for (int i = 0; b - i >= 0 && c - i >= 0; ++i) {
        if (b - i - 1 >= 0) r = r + dfs(a - 1, b - i - 1, c - i);
        if (c - i - 1 >= 0) r = r + dfs(a - 1, b - i, c - i - 1);
    }
    return dp[a][b][c] = r;
}

int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N; cin >> N;
        if (N == 1) { cout << "Case " << tc << ": 1\n"; continue; }
        int M = N / 3;
        memset(visited, 0, sizeof visited);
        BigInt r = (M % 2 == 0) ? (dfs(M, M, M) + dfs(M / 2, M / 2, M / 2)) / 2 : dfs(M, M, M) / 2;
        cout << "Case " << tc << ": " << r << "\n";
    }
    return 0;
}
