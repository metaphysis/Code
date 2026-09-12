#include <bits/stdc++.h>
using namespace std;

struct Op {
    int type, x, y, a, b, c;
};

int findNext(int x, vector<int> &fa) {
    int r = x, t;
    while (fa[r] != r) r = fa[r];
    while (x != r) {
        t = fa[x];
        fa[x] = r;
        x = t;
    }
    return r;
}

bool getRange(const Op &op, int row, int &l, int &r) {
    int d, z;
    long long t;
    if (op.type == 0) {
        d = row - op.x;
        if (abs(d) > op.a) return false;
        t = 1LL * op.a * op.a - 1LL * d * d;
        z = (int)sqrt((double)t);
        while (1LL * (z + 1) * (z + 1) <= t) z++;
        while (1LL * z * z > t) z--;
        l = op.y - z;
        r = op.y + z;
    } else if (op.type == 1) {
        d = row - op.x;
        if (abs(d) > op.a) return false;
        z = op.a - abs(d);
        l = op.y - z;
        r = op.y + z;
    } else if (op.type == 2) {
        if (row < op.x || row >= op.x + op.a) return false;
        l = op.y;
        r = op.y + op.b - 1;
    } else {
        d = row - op.x;
        if (d < 0 || d > op.a / 2) return false;
        z = op.a / 2 - d;
        l = op.y - z;
        r = op.y + z;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q, i, row, l, r, p, base;
    long long cnt[10];
    string s;
    while (cin >> n >> m >> q) {
        vector<Op> ops(q);
        vector<int> fa(n * (m + 1));
        memset(cnt, 0, sizeof(cnt));
        for (i = 0; i < q; i++) {
            cin >> s;
            if (s == "Circle") {
                ops[i].type = 0;
                cin >> ops[i].x >> ops[i].y >> ops[i].a >> ops[i].c;
            } else if (s == "Diamond") {
                ops[i].type = 1;
                cin >> ops[i].x >> ops[i].y >> ops[i].a >> ops[i].c;
            } else if (s == "Rectangle") {
                ops[i].type = 2;
                cin >> ops[i].x >> ops[i].y >> ops[i].a >> ops[i].b >> ops[i].c;
            } else {
                ops[i].type = 3;
                cin >> ops[i].x >> ops[i].y >> ops[i].a >> ops[i].c;
                if (ops[i].a % 2 == 0) ops[i].a--;
            }
        }
        for (i = 0; i < n * (m + 1); i++) fa[i] = i;
        for (i = q - 1; i >= 0; i--) {
            for (row = 0; row < n; row++) {
                if (!getRange(ops[i], row, l, r)) continue;
                l = max(l, 0);
                r = min(r, m - 1);
                if (l > r) continue;
                base = row * (m + 1);
                p = findNext(base + l, fa);
                while (p <= base + r) {
                    cnt[ops[i].c]++;
                    fa[p] = findNext(p + 1, fa);
                    p = findNext(p, fa);
                }
            }
        }
        for (i = 1; i <= 9; i++) {
            if (i > 1) cout << ' ';
            cout << cnt[i];
        }
        cout << '\n';
    }
    return 0;
}
