// Honorary Tickets
// UVa ID: 11895
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.530s

#include <bits/stdc++.h>
using namespace std;

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

__int128 gcd128(__int128 a, __int128 b) {
    while (b) {
        __int128 t = b;
        b = a % b;
        a = t;
    }
    return a;
}

struct Fraction {
    long long p, q;
    long long t;
    Fraction(long long _p, long long _q, long long _t) : p(_p), q(_q), t(_t) {
        simplify();
    }
    void simplify() {
        long long g = gcdll(p, q);
        p /= g;
        q /= g;
    }
    void update() {
        __int128 np = (__int128)p * (t - 1);
        __int128 nq = (__int128)q * t;
        __int128 g = gcd128(np, nq);
        np /= g;
        nq /= g;
        p = (long long)np;
        q = (long long)nq;
    }
    bool operator<(const Fraction& other) const {
        __int128 lhs = (__int128)p * other.q;
        __int128 rhs = (__int128)other.p * q;
        if (lhs != rhs) return lhs < rhs;
        return t < other.t;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, K;
        scanf("%d%d", &N, &K);
        priority_queue<Fraction> pq;
        for (int i = 0; i < N; ++i) {
            long long ti, li;
            scanf("%lld%lld", &ti, &li);
            pq.push(Fraction(li, ti, ti));
        }
        for (int i = 1; i < K; ++i) {
            Fraction f = pq.top();
            pq.pop();
            f.update();
            pq.push(f);
        }
        Fraction ans = pq.top();
        printf("%lld/%lld\n", ans.p, ans.q);
    }
    return 0;
}
