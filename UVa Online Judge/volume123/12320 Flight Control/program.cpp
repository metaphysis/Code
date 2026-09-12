#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12L;
const long double disEps = 1e-10L;

struct Vec {
    long double x, y, z;
};

struct Seg {
    Vec p, v;
    long double st, ed;
};

Vec add(Vec a, Vec b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec sub(Vec a, Vec b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec mul(Vec a, long double k) {
    return {a.x * k, a.y * k, a.z * k};
}

long double dot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec posAt(Seg s, long double t) {
    return add(s.p, mul(s.v, t - s.st));
}

vector<Seg> buildSeg(vector<Vec> p, int sp) {
    vector<Seg> seg;
    long double now = 0;
    p.push_back({0, 0, 0});
    for (int i = 0; i + 1 < (int)p.size(); i++) {
        Vec d = sub(p[i + 1], p[i]);
        long double len = sqrtl(dot(d, d));
        long double dt = len / sp;
        Vec v = mul(d, 1.0L * sp / len);
        seg.push_back({p[i], v, now, now + dt});
        now += dt;
    }
    return seg;
}

bool getWarn(Vec d, Vec v, long double dt, long double lim, long double &lef, long double &rig) {
    long double a = dot(v, v), b = 2.0L * dot(d, v), c = dot(d, d) - lim * lim;
    if (a < eps) {
        if (c <= 0) {
            lef = 0;
            rig = dt;
            return true;
        }
        return false;
    }
    long double delta = b * b - 4.0L * a * c;
    long double tol = 1e-18L * (b * b + fabsl(4.0L * a * c) + 1.0L);
    if (delta < -tol) return false;
    if (delta < 0) delta = 0;
    long double sq = sqrtl(delta);
    long double x1 = (-b - sq) / (2.0L * a);
    long double x2 = (-b + sq) / (2.0L * a);
    lef = max(0.0L, x1);
    rig = min(dt, x2);
    return lef <= rig + eps;
}

int solve(vector<Seg> a, vector<Seg> b, int ra, int rb) {
    int i = 0, j = 0, ans = 0;
    bool inWarn = false;
    long double lim = ra + rb + disEps;
    while (i < (int)a.size() && j < (int)b.size()) {
        long double st = max(a[i].st, b[j].st), ed = min(a[i].ed, b[j].ed);
        if (ed - st > eps) {
            Vec pa = posAt(a[i], st), pb = posAt(b[j], st);
            Vec d = sub(pa, pb), v = sub(a[i].v, b[j].v);
            long double lef, rig, dt = ed - st;
            if (getWarn(d, v, dt, lim, lef, rig)) {
                if (!inWarn || lef > eps) ans++;
                inWarn = rig >= dt - eps;
            } else {
                inWarn = false;
            }
        }
        if (a[i].ed < b[j].ed - eps) i++;
        else if (b[j].ed < a[i].ed - eps) j++;
        else {
            i++;
            j++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int ra, sa, ka, rb, sb, kb;
        cin >> ra >> sa >> ka;
        vector<Vec> pa(ka);
        for (int i = 0; i < ka; i++) cin >> pa[i].x >> pa[i].y >> pa[i].z;
        cin >> rb >> sb >> kb;
        vector<Vec> pb(kb);
        for (int i = 0; i < kb; i++) cin >> pb[i].x >> pb[i].y >> pb[i].z;
        vector<Seg> a = buildSeg(pa, sa), b = buildSeg(pb, sb);
        cout << solve(a, b, ra, rb) << '\n';
    }
    return 0;
}
