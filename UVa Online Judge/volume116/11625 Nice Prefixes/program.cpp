// Nice Prefixes
// UVa ID: 11625
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 3.550s

#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007LL;

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

vector<long long> multiply(const vector<long long>& a, const vector<long long>& b) {
    vector<long long> c(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); ++i) if (a[i])
        for (size_t j = 0; j < b.size(); ++j) if (b[j])
            c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
    return c;
}

// Berlekamp-Massey 求线性递推系数 rec，满足 a_n = rec[0]a_{n-1}+...+rec[d-1]a_{n-d}
vector<long long> berlekampMassey(const vector<long long>& s) {
    vector<long long> C(1, 1), B(1, 1);
    long long b = 1;
    int L = 0, m = 1;
    for (int n = 0; n < (int)s.size(); ++n) {
        long long d = 0;
        for (int i = 0; i <= L; ++i) d = (d + C[i] * s[n - i]) % MOD;
        if (d == 0) { ++m; continue; }
        vector<long long> T = C;
        long long coef = d * modPow(b, MOD - 2) % MOD;
        if ((int)C.size() < (int)B.size() + m) C.resize(B.size() + m, 0);
        for (int j = 0; j < (int)B.size(); ++j)
            C[j + m] = (C[j + m] - coef * B[j]) % MOD;
        if (2 * L <= n) {
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else ++m;
    }
    vector<long long> rec(L);
    for (int i = 1; i <= L; ++i) rec[i - 1] = (MOD - C[i]) % MOD;
    return rec;
}

// Bostan-Mori 求线性递推第 n 项（n 从 0 开始）
long long bostanMori(long long n, const vector<long long>& rec, const vector<long long>& init) {
    int d = (int)rec.size();
    if (n < (long long)init.size()) return init[n];
    vector<long long> Q(d + 1, 0);
    Q[0] = 1;
    for (int i = 0; i < d; ++i) Q[i + 1] = (MOD - rec[i]) % MOD;
    vector<long long> P(d, 0);
    for (int i = 0; i < d; ++i)
        for (int j = 0; j <= i; ++j)
            P[i] = (P[i] + init[i - j] * Q[j]) % MOD;
    while (n > 0) {
        vector<long long> Qm(Q.size());
        for (int i = 0; i < (int)Q.size(); ++i)
            Qm[i] = (i & 1) ? (MOD - Q[i]) % MOD : Q[i];
        vector<long long> S = multiply(P, Qm);
        vector<long long> T = multiply(Q, Qm);
        vector<long long> newP, newQ;
        int parity = (int)(n & 1);
        for (int i = parity; i < (int)S.size(); i += 2) newP.push_back(S[i]);
        for (int i = 0; i < (int)T.size(); i += 2) newQ.push_back(T[i]);
        P = newP;
        Q = newQ;
        n >>= 1;
    }
    return P[0] % MOD;
}

long long solveCase(long long L, int K) {
    // 构建状态 (a,b) 表示有 a 个低类（计数为 base），b 个中类（base+1），c=K-a-b 个高类（base+2）
    vector<pair<int,int>> states;
    int id[105][105];
    memset(id, -1, sizeof(id));
    for (int a = 1; a <= K; ++a)
        for (int b = 0; b <= K - a; ++b) {
            id[a][b] = (int)states.size();
            states.push_back({a, b});
        }
    int nState = (int)states.size();
    // 预计算转移
    vector<vector<pair<int,long long>>> trans(nState);
    for (int idx = 0; idx < nState; ++idx) {
        int a = states[idx].first, b = states[idx].second;
        int c = K - a - b;
        // 选择低类
        if (a > 1) {
            int na = a - 1, nb = b + 1;
            trans[idx].push_back({id[na][nb], a});
        } else { // a == 1
            int na = b + 1, nb = c; // c = K - 1 - b
            trans[idx].push_back({id[na][nb], 1});
        }
        // 选择中类
        if (b > 0) {
            int na = a, nb = b - 1;
            trans[idx].push_back({id[na][nb], b});
        }
    }
    int maxLen = 2 * nState + 10;
    vector<long long> seq;
    seq.reserve(maxLen);
    vector<long long> dp(nState, 0), ndp(nState);
    dp[id[K][0]] = 1;
    for (int len = 0; len < maxLen; ++len) {
        long long total = 0;
        for (int i = 0; i < nState; ++i) total = (total + dp[i]) % MOD;
        seq.push_back(total);
        if (len + 1 == maxLen) break;
        fill(ndp.begin(), ndp.end(), 0);
        for (int i = 0; i < nState; ++i) if (dp[i]) {
            for (auto &e : trans[i]) {
                int j = e.first;
                long long w = e.second;
                ndp[j] = (ndp[j] + dp[i] * w) % MOD;
            }
        }
        dp.swap(ndp);
    }
    vector<long long> rec = berlekampMassey(seq);
    int d = (int)rec.size();
    if (d == 0) return 0; // 不会发生
    vector<long long> init(seq.begin(), seq.begin() + d);
    return bostanMori(L, rec, init);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long L;
        int K;
        cin >> L >> K;
        cout << solveCase(L, K) << '\n';
    }
    return 0;
}
