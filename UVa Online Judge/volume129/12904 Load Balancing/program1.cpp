// Load Balancing
// UVa ID: 12904
// Verdict: Accepted
// Submission Date: 2023-04-22
// UVa Run Time: 0.230s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 256;

int T[256];

void add(int x, int delta){
    for (int i = x; i < MAXN; i = i | (i + 1))
        T[i] += delta;
}

int get(int x) {
    int sum = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        sum += T[i];
    return sum;
}

int sum(int L, int R) { return get(R) - get(L - 1); }

struct fraction {
    long long n, d;
    fraction (long long n = 0, long long d = 0): n(n), d(d) {}
    fraction diff(fraction c) {
        fraction r;
        r.n = abs(n * c.d - d * c.n), r.d = d * c.d;
        return r;
    }
    fraction add(fraction c) {
        fraction r;
        r.n = n * c.d + d * c.n, r.d = d * c.d;
        return r;
    }
    bool operator<(const fraction &c) const {
        return n * c.d < d * c.n;
    }
} best;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> n;
        memset(T, 0, sizeof T);
        for (int i = 0, c; i < n; i++) {
            cin >> c;
            add(c, 1);
        }
        best.n = 10000, best.d = 1;
        int besta, bestb, bestc;
        fraction f1, f2, f3;
        for (int a = 0; a <= 160; a++) {
            fraction f1 = fraction(sum(0, a), 1).diff(fraction(n, 4));
            if (best < f1) continue;
            for (int b = a + 1; b <= 160; b++) {
                fraction f2 = f1.add(fraction(sum(a + 1, b), 1).diff(fraction(n, 4)));
                if (best < f2) continue;
                for (int c = b + 1; c <= 160; c++) {
                    fraction f3 = f2.add(fraction(sum(b + 1, c), 1).diff(fraction(n, 4)));
                    if (best < f3) continue;
                    f3 = f3.add(fraction(sum(c + 1, 160), 1).diff(fraction(n, 4)));
                    if (f3 < best)
                        best =f3, besta = a, bestb = b, bestc = c;
                }
            }
        }
        cout << "Case " << cs << ": ";
        cout << besta << ' ' << bestb << ' ' << bestc << '\n';
    }
    return 0;
}
