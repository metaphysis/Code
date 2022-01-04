#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50010, MAXB = 256;

int n, s, a[MAXN], link[MAXN], added[MAXB];

void update(int L, int R, int x) {
    int p = link[L], q = link[R];
    for (int i = L; i <= min(R, p * s); i++) a[i] += x;
    for (int i = p + 1; i < q; i++) added[i] += x;
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= R; i++) a[i] += x;
    }
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
    }
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) update(L, R, x);
        else cout << a[R] + added[(R - 1) / s + 1] << '\n';
    }
    return 0;
}
