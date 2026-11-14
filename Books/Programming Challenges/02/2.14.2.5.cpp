#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010, MAXB = 256;

int n, s, a[MAXN], link[MAXN], sum[MAXB], flag[MAXB];

int query(int L, int R)
{
    int p = link[L], q = link[R];
    int r = 0;
    for (int i = L; i <= min(R, p * s); i++) r += a[i];
    for (int i = p + 1; i < q; i++) r += sum[i];
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) r += a[i];
    }
    return r;
}

void modify(int block, int idx)
{
    sum[block] -= a[idx];
    a[idx] = (int)sqrt(a[idx]);
    sum[block] += a[idx];
}

void update(int L, int R)
{
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) modify(p, i);
    for (int i = p + 1; i < q; i++) {
        if (flag[i]) continue;
        flag[i] = 1;
        for (int j = (i - 1) * s + 1; j <= i * s; j++) {
            if (a[j] > 1) flag[i] = 0;
            modify(i, j);
        }
    }
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) modify(q, i);
    }
}

int main(int argc, char *argv[])
{
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
        if (c == 0) update(L, R);
        else cout << query(L, R) << '\n';
    }
    return 0;
}
