#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, MAXB = 320;

int n, s, a[MAXN], link[MAXN], setted[MAXB], value[MAXB];

void update(int b) {
    if (!setted[b]) return;
    for (int i = (b - 1) * s + 1; i <= min(n, b * s); i++)
        a[i] = value[b];
    setted[b] = 0;
}

int query(int L, int R, int x) {
    int r = 0;
    int p = link[L], q = link[R];
    update(p);
    for (int i = L; i <= min(R, p * s); i++) {
        if (a[i] == x) r++;
        a[i] = x;
    }
    for (int i = p + 1; i < q; i++) {
        if (setted[i]) {
            if (value[i] == x) r += s;
            value[i] = x;
        } else {
            for (int j = (i - 1) * s + 1; j <= i * s; j++)
                if (a[j] == x) r++;
            setted[i] = 1;
            value[i] = x;
        }
    }
    if (p != q) {
        update(q);
        for (int i = (q - 1) * s + 1; i <= R; i++) {
            if (a[i] == x) r++;
            a[i] = x;
        }
    }
    return r;
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
    }
    int L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> L >> R >> x;
        cout << query(L, R, x) << '\n';
    }
    return 0;
}
