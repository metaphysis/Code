#include <bits/stdc++.h>
using namespace std;

using Func = array<int, 10>;

int tab[10][10];

Func getId() {
    Func f;
    int i;
    for (i = 0; i < 10; i++) f[i] = i;
    return f;
}

Func mergeFunc(const Func &a, const Func &b) {
    Func f;
    int i;
    for (i = 0; i < 10; i++) f[i] = b[a[i]];
    return f;
}

Func getRep(Func base, unsigned long long cnt) {
    Func res = getId();
    while (cnt > 0) {
        if (cnt & 1) res = mergeFunc(res, base);
        base = mergeFunc(base, base);
        cnt >>= 1;
    }
    return res;
}

Func getRun(int dig, unsigned long long len) {
    Func f;
    int i;
    for (i = 0; i < 10; i++) f[i] = tab[i][dig];
    return getRep(f, len);
}

Func getCycle(unsigned long long p) {
    Func res = getId();
    int i;
    for (i = 0; i < 10; i++) res = mergeFunc(res, getRun(i, p));
    return res;
}

int getDigit(unsigned long long x, unsigned long long p) {
    return x / p % 10;
}

int applyRange(int st, unsigned long long l, unsigned long long r, unsigned long long p) {
    unsigned long long per, rem, cnt, end, rr, len;
    Func cyc, f;
    int dig;
    per = p * 10;
    while (l <= r) {
        rem = l % per;
        if (rem == 0) {
            cnt = (r - l + 1) / per;
            if (cnt > 0) {
                cyc = getCycle(p);
                f = getRep(cyc, cnt);
                st = f[st];
                l += cnt * per;
                continue;
            }
        }
        dig = getDigit(l, p);
        end = (l / p + 1) * p - 1;
        rr = min(r, end);
        len = rr - l + 1;
        f = getRun(dig, len);
        st = f[st];
        l = rr + 1;
    }
    return st;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long a, b, p;
    int ans[19];
    int i, j, st, hi;
    while (cin >> tab[0][0]) {
        for (j = 1; j < 10; j++) cin >> tab[0][j];
        for (i = 1; i < 10; i++)
            for (j = 0; j < 10; j++) cin >> tab[i][j];
        cin >> a >> b;
        p = 1;
        for (i = 0; i < 19; i++) {
            st = getDigit(a, p);
            if (a < b) st = applyRange(st, a + 1, b, p);
            ans[i] = st;
            if (i < 18) p *= 10;
        }
        hi = 18;
        while (hi > 0 && ans[hi] == 0) hi--;
        for (i = hi; i >= 0; i--) cout << ans[i];
        cout << '\n';
    }
    return 0;
}
