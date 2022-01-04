#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, MAXB = 1300;

int n, nn, s, a[MAXN], b[MAXN], link[MAXN], mode[MAXB][MAXB], cnt[MAXN];
vector<int> idx[MAXN];
int tmp[MAXB * 2], tot;

int query(int L, int R) {
    tot = 0;
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) tmp[tot++] = a[i];
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) tmp[tot++] = a[i];
    }
    if (p + 2 <= q) tmp[tot++] = mode[p + 1][q - 1];
    int m = -1, c = 0;
    for (int i = 0; i < tot; i++) {
        int x = tmp[i];
        int tot = upper_bound(idx[x].begin(), idx[x].end(), R) -
            lower_bound(idx[x].begin(), idx[x].end(), L);
        if (tot > c || (tot == c && x < m)) {
            c = tot;
            m = x;
        }
    }
    return b[m];
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n / log2(n)) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i - 1] = a[i];
        link[i] = (i - 1) / s + 1;
    }
    sort(b, b + n);
    nn = unique(b, b + n) - b;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b, b + nn, a[i]) - b;
        idx[a[i]].push_back(i);
    }
    int blocks = (n - 1) / s + 1;
    for (int i = 1; i <= blocks; i++) {
        int m = -1, c = 0;
        for (int j = 0; j < nn; j++) cnt[j] = 0;
        for (int j = i; j <= blocks; j++) {
            for (int k = (j - 1) * s + 1; k <= min(n, j * s); k++) {
                cnt[a[k]]++;
                if (cnt[a[k]] > c || (cnt[a[k]] == c && a[k] < m)) {
                    c = cnt[a[k]];
                    m = a[k];
                }
            }
            mode[i][j] = m;
        }
    }
    int L, R;
    for (int i = 0; i < n; i++) {
        cin >> L >> R;
        cout << query(L, R) << '\n';
    }
    return 0;
}
