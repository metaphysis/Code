#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

long long roundRat(long long n, long long d) {
    long long a = llabs(n), k = sqrtl((long double)a * a / d);
    while ((k + 1) * (k + 1) * d <= a * a) ++k;
    while (k * k * d > a * a) --k;
    if (4 * a * a >= (2 * k + 1) * (2 * k + 1) * d) ++k;
    return n < 0 ? -k : k;
}

Pt rotatePt(Pt p, int u, int v) {
    long long d = 1LL * u * u + 1LL * v * v;
    long long a = 1LL * u * p.x - 1LL * v * p.y;
    long long b = 1LL * v * p.x + 1LL * u * p.y;
    return {roundRat(a, d), roundRat(b, d)};
}

bool solveAxis(array<long long, 3> q, array<long long, 3> t, long long &s, long long &b, bool &freeScale) {
    int i, j;
    freeScale = false;
    for (i = 0; i < 3; ++i)
        for (j = i + 1; j < 3; ++j)
            if (q[i] != q[j]) {
                long long dq = q[j] - q[i], dt = t[j] - t[i];
                if (dt % dq != 0) return false;
                s = dt / dq;
                if (s == 0) return false;
                b = t[i] - s * q[i];
                for (int k = 0; k < 3; ++k)
                    if (s * q[k] + b != t[k]) return false;
                return true;
            }
    if (t[0] != t[1] || t[1] != t[2]) return false;
    freeScale = true;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, int>> rot;
    for (int u = -10; u <= 10; ++u) {
        rot.push_back({u, -10});
        rot.push_back({u, 10});
    }
    for (int v = -9; v <= 9; ++v) {
        rot.push_back({-10, v});
        rot.push_back({10, v});
    }
    int tc = 0;
    while (true) {
        array<Pt, 3> a, z;
        bool allZero = true, hasFree = false;
        for (int i = 0; i < 3; ++i) {
            if (!(cin >> a[i].x >> a[i].y)) return 0;
            if (a[i].x != 0 || a[i].y != 0) allZero = false;
        }
        if (allZero) break;
        for (int i = 0; i < 3; ++i)
            cin >> z[i].x >> z[i].y;
        set<tuple<int, int, long long, long long, long long, long long>> ways;
        for (auto r : rot) {
            array<Pt, 3> q;
            array<int, 3> p = {0, 1, 2};
            for (int i = 0; i < 3; ++i) q[i] = rotatePt(a[i], r.first, r.second);
            do {
                array<long long, 3> qx, qy, tx, ty;
                long long sx, sy, bx, by;
                bool fx, fy;
                for (int i = 0; i < 3; ++i) {
                    qx[i] = q[i].x;
                    qy[i] = q[i].y;
                    tx[i] = z[p[i]].x;
                    ty[i] = z[p[i]].y;
                }
                if (!solveAxis(qx, tx, sx, bx, fx) || !solveAxis(qy, ty, sy, by, fy)) continue;
                if (fx || fy) {
                    hasFree = true;
                    continue;
                }
                int u = r.first, v = r.second;
                if (u < 0 || (u == 0 && v < 0)) {
                    u = -u;
                    v = -v;
                    sx = -sx;
                    sy = -sy;
                }
                ways.insert({u, v, sx, sy, bx, by});
            } while (next_permutation(p.begin(), p.end()));
        }
        ++tc;
        cout << "Case " << tc << ": ";
        if (ways.empty() && !hasFree) cout << "no solution\n";
        else if (hasFree || ways.size() > 1) cout << "inconsistent solutions\n";
        else cout << "equivalent solutions\n";
    }
    return 0;
}
