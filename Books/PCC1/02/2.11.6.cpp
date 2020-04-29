#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

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

void update(int p, int v)
{
    sum[link[p]] -= a[p];
    a[p] = v;
    sum[link[p]] += a[p];
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
