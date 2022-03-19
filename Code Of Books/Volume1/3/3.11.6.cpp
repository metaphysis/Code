#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000010, MAXB = 10010;

int n, s, a[MAXN], link[MAXN], sum[MAXN];

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

int flag[MAXB];

void setValue(int block, int idx, int value)
{
    sum[block] -= a[idx];
    a[idx] = value;
    sum[block] += a[idx];
}

void update(int L, int R)
{
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) setValue(p, i, sqrt(a[i]));
    for (int i = p + 1; i < q; i++) {
        if (flag[i]) continue;
        flag[i] = 1;
        for (int j = (i - 1) * s; j <= i * s; j++) {
            int tmp = sqrt(a[j]);
            if (tmp != a[j]) flag[i] = 0;
            setValue(i, j, tmp);
        }
    }
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) setValue(q, i, sqrt(a[i]));
    }
}

int main(int argc, char *argv[])
{
    
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= s; i++) sum[i] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
        sum[link[i]] += a[i];
    }
    int m, L, R;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> L >> R;
        cout << query(L, R) << " = " << (L + R) * (R - L + 1) / 2 << '\n';
        
    }
    return 0;
}
