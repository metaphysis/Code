#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Vec {
    double x, y, z;
    Vec(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Vec operator + (const Vec &b) const { return Vec(x + b.x, y + b.y, z + b.z); }
    Vec operator - (const Vec &b) const { return Vec(x - b.x, y - b.y, z - b.z); }
    Vec operator * (double k) const { return Vec(x * k, y * k, z * k); }
};

double dot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec cross(Vec a, Vec b) {
    return Vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double len(Vec a) {
    return sqrt(dot(a, a));
}

Vec unit(Vec a) {
    return a * (1.0 / len(a));
}

bool same(Vec a, Vec b) {
    return len(a - b) < 1e-7;
}

void uniquePoints(vector<Vec> &p) {
    vector<Vec> q;
    for (Vec a : p) {
        bool ok = true;
        for (Vec b : q)
            if (same(a, b)) ok = false;
        if (ok) q.push_back(a);
    }
    p = q;
}

void clip(vector<vector<Vec>> &fs, Vec n, double d) {
    vector<vector<Vec>> nf;
    bool hasIn = false, hasOut = false;
    for (vector<Vec> f : fs) {
        vector<Vec> g;
        int m = f.size();
        for (int i = 0; i < m; i++) {
            Vec p = f[i], q = f[(i + 1) % m];
            double dp = dot(n, p) - d, dq = dot(n, q) - d;
            bool ip = dp <= eps, iq = dq <= eps;
            if (dp < -eps) hasIn = true;
            if (dp > eps) hasOut = true;
            if (ip) g.push_back(p);
            if (ip != iq) g.push_back(p + (q - p) * (dp / (dp - dq)));
        }
        if (g.size() >= 3) nf.push_back(g);
    }
    fs = nf;
    if (!hasIn || !hasOut) return;
    vector<Vec> cap;
    for (vector<Vec> f : fs)
        for (Vec p : f)
            if (fabs(dot(n, p) - d) < 1e-7) cap.push_back(p);
    uniquePoints(cap);
    if (cap.size() < 3) return;
    Vec cen;
    for (Vec p : cap) cen = cen + p;
    cen = cen * (1.0 / cap.size());
    Vec axis = fabs(n.x) < 0.9 ? Vec(1, 0, 0) : Vec(0, 1, 0);
    Vec u = unit(cross(n, axis)), v = cross(n, u);
    sort(cap.begin(), cap.end(), [&](Vec a, Vec b) {
        a = a - cen;
        b = b - cen;
        return atan2(dot(v, a), dot(u, a)) < atan2(dot(v, b), dot(u, b));
    });
    fs.push_back(cap);
}

double volume(vector<vector<Vec>> &fs) {
    Vec o;
    int cnt = 0;
    for (vector<Vec> f : fs)
        for (Vec p : f) {
            o = o + p;
            cnt++;
        }
    o = o * (1.0 / cnt);
    double ans = 0;
    for (vector<Vec> f : fs)
        for (int i = 1; i + 1 < (int)f.size(); i++)
            ans += fabs(dot(cross(f[i] - o, f[i + 1] - o), f[0] - o)) / 6.0;
    return ans;
}

vector<vector<Vec>> cube(double a, double b, double c) {
    Vec p[8] = {Vec(0, 0, 0), Vec(a, 0, 0), Vec(a, b, 0), Vec(0, b, 0), Vec(0, 0, c), Vec(a, 0, c), Vec(a, b, c), Vec(0, b, c)};
    return {{p[0], p[1], p[2], p[3]}, {p[4], p[7], p[6], p[5]}, {p[0], p[4], p[5], p[1]}, {p[1], p[5], p[6], p[2]}, {p[2], p[6], p[7], p[3]}, {p[3], p[7], p[4], p[0]}};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tc = 0;
    double a, b, c;
    while (cin >> n) {
        if (n == 0) break;
        cin >> a >> b >> c;
        vector<Vec> p(n);
        for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y >> p[i].z;
        cout << fixed << setprecision(3) << "Case " << ++tc << ":";
        for (int i = 0; i < n; i++) {
            vector<vector<Vec>> fs = cube(a, b, c);
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                Vec nrm = p[j] - p[i];
                double d = (dot(p[j], p[j]) - dot(p[i], p[i])) / 2.0;
                clip(fs, nrm, d);
            }
            cout << " " << volume(fs) / (a * b * c);
        }
        cout << '\n';
    }
    return 0;
}
