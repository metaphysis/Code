// Bulb inside a Grid
// UVa ID: 11591
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int r0[200], r1[200], c0[200], c1[200];
set<int> rs, cs;

void addRect(int a, int b, int c, int d) {
    if (b >= n && d >= n) {
        r0[k] = a; r1[k] = n - 1; c0[k] = c; c1[k] = n - 1;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
        r0[k] = a; r1[k] = n - 1; c0[k] = 0; c1[k] = d - n;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
        r0[k] = 0; r1[k] = b - n; c0[k] = c; c1[k] = n - 1;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
        r0[k] = 0; r1[k] = b - n; c0[k] = 0; c1[k] = d - n;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
    } else if (b >= n) {
        r0[k] = a; r1[k] = n - 1; c0[k] = c; c1[k] = d;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
        r0[k] = 0; r1[k] = b - n; c0[k] = c; c1[k] = d;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
    } else if (d >= n) {
        r0[k] = a; r1[k] = b; c0[k] = c; c1[k] = n - 1;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
        r0[k] = a; r1[k] = b; c0[k] = 0; c1[k] = d - n;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
    } else {
        r0[k] = a; r1[k] = b; c0[k] = c; c1[k] = d;
        rs.insert(r0[k]); rs.insert(r1[k] + 1); cs.insert(c0[k]); cs.insert(c1[k] + 1); ++k;
    }
}

long long tri(long long x) {
    return x * (x + 1) / 2;
}

long long black(long long a, long long b, long long c, long long d) {
    if (c > b - 1) return (b - a) * (d - c);
    if (d - 1 <= a) return 0;
    if (b - 1 <= d - 2) {
        if (c - 1 >= a) return tri(b - c + 1) + (c - a - 1) * (d - c) + (b - c + 1) * (d - b - 1);
        return tri(b - a) + (b - a) * (d - b - 1);
    } else {
        if (a + 1 >= c) return tri(d - a - 1);
        return tri(d - c) + (c - a - 1) * (d - c);
    }
    return 0;
}

int main() {
    int t;
    char line[100];
    scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int q;
        scanf("%d %d\n", &n, &q);
        rs.clear();
        cs.clear();
        rs.insert(0);
        rs.insert(n);
        cs.insert(0);
        cs.insert(n);
        k = 0;
        for (int i = 0; i < q; ++i) {
            fgets(line, 100, stdin);
            int len = strlen(line);
            for (int j = 0; j < len; ++j) {
                if (line[j] < '0' || line[j] > '9') line[j] = ' ';
            }
            istringstream in(line);
            vector<int> v;
            int x;
            while (in >> x) v.push_back(x);
            int a = v[0] - 1;
            int c = v[1] - 1;
            int d = c + v[2] - 1;
            if (v.size() == 4 && v[3] % 2 == 1) addRect(a, a + v[2] - 1, c, d);
            if (v.size() == 5 && v[4] % 2 == 1) addRect(a, a + v[3] - 1, c, d);
        }
        vector<int> rv(rs.begin(), rs.end());
        vector<int> cv(cs.begin(), cs.end());
        int nr = rv.size(), nc = cv.size();
        bool flip[nr - 1][nc - 1];
        memset(flip, 0, sizeof(flip));
        for (int z = 0; z < k; ++z) {
            for (int i = 0; i + 1 < nr; ++i) {
                if (r0[z] <= rv[i] && rv[i + 1] - 1 <= r1[z]) {
                    for (int j = 0; j + 1 < nc; ++j) {
                        if (c0[z] <= cv[j] && cv[j + 1] - 1 <= c1[z]) flip[i][j] ^= 1;
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i + 1 < nr; ++i) {
            for (int j = 0; j + 1 < nc; ++j) {
                long long total = (long long)(rv[i + 1] - rv[i]) * (cv[j + 1] - cv[j]);
                long long cnt = black(rv[i], rv[i + 1], cv[j], cv[j + 1]);
                ans += flip[i][j] ? cnt : total - cnt;
            }
        }
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
