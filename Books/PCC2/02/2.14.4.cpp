#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010, MAXB = 256;

int n, s, a[MAXN], link[MAXN];
long long added[MAXB], sum[MAXB];

int query(int L, int R, int x) {
    int p = link[L], q = link[R];
    long long r = 0;
    for (int i = L; i <= min(R, p * s); i++) r += a[i] + added[p], r %= x;
    for (int i = p + 1; i < q; i++) r += sum[i], r %= x;
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) r += a[i] + added[q], r %= x;
    }
    return r;
}

void modify(int block, int idx, int x) {
    sum[block] -= a[idx];
    a[idx] += x;
    sum[block] += a[idx];
}

void update(int L, int R, int x) {
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) modify(p, i, x);
    for (int i = p + 1; i < q; i++) added[i] += x, sum[i] += x * s;
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) modify(q, i, x);
    }
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
        sum[link[i]] += a[i];
    }
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) update(L, R, x);
        else { x += 1; cout << query(L, R, x) << '\n'; }
    }
    return 0;
}
