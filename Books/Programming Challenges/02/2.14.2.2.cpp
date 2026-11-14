#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010, MAXB = 1010;

int n, s, a[MAXN], link[MAXN];
int sorted[MAXB][MAXB], cnt[MAXB];
int added[MAXB];

int query(int L, int R, int x) {
    int p = link[L], q = link[R];
    int r = 0;
    for (int i = L; i <= min(R, p * s); i++) r += (a[i] + added[p] < x);
    for (int i = p + 1; i < q; i++)
        r += lower_bound(sorted[i], sorted[i] + cnt[i], x - added[i]) - sorted[i];
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) r += (a[i] + added[q] < x);
    }
    return r;
}

void resort(int block) {
    cnt[block] = 0;
    for (int i = (block - 1) * s + 1; i <= min(block * s, n); i++)
        sorted[block][cnt[block]++] = a[i];
    sort(sorted[block], sorted[block] + cnt[block]);
}

void update(int L, int R, int x) {
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) a[i] += x;
    resort(p);
    for (int i = p + 1; i < q; i++) added[i] += x;
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) a[i] += x;
        resort(q);
    }
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n / log2(n)) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
        sorted[link[i]][cnt[link[i]]++] = a[i];
    }
    int blocks = (n - 1) / s + 1;
    for (int i = 1; i <= blocks; i++) sort(sorted[i], sorted[i] + cnt[i]);
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) update(L, R, x);
        else { x *= x; cout << query(L, R, x) << '\n'; }
    }
    return 0;
}
