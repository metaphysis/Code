#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, MAXB = 320;

int n, s, a[MAXN], link[MAXN];
int sorted[MAXB][MAXB], cnt[MAXB];
int added[MAXB];

int query(int L, int R, int x) {
    int p = link[L], q = link[R];
    int r = -1;
    for (int i = L; i <= min(R, p * s); i++)
        if (a[i] + added[p] < x)
            r = max(r, a[i] + added[p]);
    for (int i = p + 1; i < q; i++) {
        int idx = lower_bound(sorted[i], sorted[i] + cnt[i], x - added[i]) - sorted[i];
        if (idx) r = max(r, sorted[i][idx - 1] + added[i]);
    }
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++)
            if (a[i] + added[q] < x)
                r = max(r, a[i] + added[q]);
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
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
        sorted[link[i]][cnt[link[i]]++] = a[i];
    }
    for (int i = 1; i <= s; i++) sort(sorted[i], sorted[i] + cnt[i]);
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) update(L, R, x);
        else cout << query(L, R, x) << '\n';
    }
    return 0;
}
