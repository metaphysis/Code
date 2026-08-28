#include <bits/stdc++.h>
using namespace std;

const double infVal = 1e100;
const double epsVal = 1e-10;
const double earthR = 6370.0;

struct Vec {
    double x, y, z;
    Vec operator + (const Vec& o) const {
        return {x + o.x, y + o.y, z + o.z};
    }
    Vec operator - (const Vec& o) const {
        return {x - o.x, y - o.y, z - o.z};
    }
    Vec operator * (double k) const {
        return {x * k, y * k, z * k};
    }
};

double dotVal(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec crossVal(const Vec& a, const Vec& b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

double normVal(const Vec& a) {
    return sqrt(dotVal(a, a));
}

Vec unitVal(const Vec& a) {
    double len = normVal(a);
    return a * (1.0 / len);
}

double fixAng(double x) {
    double pi2 = 2.0 * acos(-1.0);
    while (x < 0.0) x += pi2;
    while (x >= pi2) x -= pi2;
    return x;
}

Vec arcPoint(const Vec& a, const Vec& v, double ang) {
    return a * cos(ang) + v * sin(ang);
}

Vec cirPoint(const Vec& cen, const Vec& e1, const Vec& e2, double cs, double sn, double ang) {
    return cen * cs + (e1 * cos(ang) + e2 * sin(ang)) * sn;
}

void addRoots(vector<double>& vals, double k0, double aa, double bb, double tar, double lim) {
    double amp, rat, pha, del, x;
    int k;
    amp = hypot(aa, bb);
    if (amp < epsVal) return;
    rat = (tar - k0) / amp;
    if (rat < -1.0 - epsVal || rat > 1.0 + epsVal) return;
    rat = max(-1.0, min(1.0, rat));
    pha = atan2(bb, aa);
    del = acos(rat);
    for (k = -2; k <= 2; k++) {
        x = pha + del + 2.0 * acos(-1.0) * k;
        if (x > epsVal && x < lim - epsVal) vals.push_back(x);
        x = pha - del + 2.0 * acos(-1.0) * k;
        if (x > epsVal && x < lim - epsVal) vals.push_back(x);
    }
}

bool inside(const Vec& p, const vector<Vec>& aps, double cs) {
    int i;
    for (i = 0; i < (int)aps.size(); i++)
        if (dotVal(p, aps[i]) >= cs - 1e-9) return true;
    return false;
}

bool greatArc(const Vec& a, const Vec& b, const vector<Vec>& aps, double cs) {
    double len, sn, mid;
    Vec v;
    vector<double> vals;
    int i, j;
    len = acos(max(-1.0, min(1.0, dotVal(a, b))));
    if (len < epsVal) return true;
    sn = sin(len);
    if (fabs(sn) < epsVal) {
        Vec ref = fabs(a.z) < 0.9 ? Vec{0.0, 0.0, 1.0} : Vec{1.0, 0.0, 0.0};
        v = unitVal(crossVal(a, ref));
    } else {
        v = (b - a * cos(len)) * (1.0 / sn);
    }
    vals.push_back(0.0);
    vals.push_back(len);
    for (i = 0; i < (int)aps.size(); i++)
        addRoots(vals, 0.0, dotVal(aps[i], a), dotVal(aps[i], v), cs, len);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end(), [](double x, double y) {
        return fabs(x - y) < 1e-9;
    }), vals.end());
    for (j = 0; j + 1 < (int)vals.size(); j++) {
        mid = (vals[j] + vals[j + 1]) * 0.5;
        if (!inside(arcPoint(a, v, mid), aps, cs)) return false;
    }
    return true;
}

bool cirArc(const Vec& cen, const Vec& e1, const Vec& e2, double cs, double sn, double st, double ed, const vector<Vec>& aps) {
    double len, mid, k0, aa, bb;
    vector<double> vals;
    int i, j;
    len = ed - st;
    vals.push_back(0.0);
    vals.push_back(len);
    for (i = 0; i < (int)aps.size(); i++) {
        k0 = cs * dotVal(aps[i], cen);
        aa = sn * dotVal(aps[i], e1);
        bb = sn * dotVal(aps[i], e2);
        addRoots(vals, k0, aa * cos(st) + bb * sin(st), -aa * sin(st) + bb * cos(st), cs, len);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end(), [](double x, double y) {
        return fabs(x - y) < 1e-9;
    }), vals.end());
    for (j = 0; j + 1 < (int)vals.size(); j++) {
        mid = (vals[j] + vals[j + 1]) * 0.5 + st;
        if (!inside(cirPoint(cen, e1, e2, cs, sn, mid), aps, cs)) return false;
    }
    return true;
}

vector<double> dijk(int src, const vector<vector<double>>& gra) {
    int n, u, v;
    double d;
    vector<double> dis;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
    n = gra.size();
    dis.assign(n, infVal);
    dis[src] = 0.0;
    que.push({0.0, src});
    while (!que.empty()) {
        d = que.top().first;
        u = que.top().second;
        que.pop();
        if (d > dis[u] + epsVal) continue;
        for (v = 0; v < n; v++) {
            if (gra[u][v] >= infVal) continue;
            if (dis[v] > d + gra[u][v]) {
                dis[v] = d + gra[u][v];
                que.push({dis[v], v});
            }
        }
    }
    return dis;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, r, q, s, t, c, cas = 1, i, j, k, m;
    double lon, lat, pi, rho, cs, sn, dval, h2, h;
    vector<Vec> aps, pts, e1, e2;
    vector<vector<pair<double, int>>> cirs;
    vector<vector<double>> geo, dist;
    while (cin >> n >> r) {
        pi = acos(-1.0);
        rho = r / earthR;
        cs = cos(rho);
        sn = sin(rho);
        aps.clear();
        for (i = 0; i < n; i++) {
            cin >> lon >> lat;
            lon *= pi / 180.0;
            lat *= pi / 180.0;
            aps.push_back({cos(lat) * cos(lon), cos(lat) * sin(lon), sin(lat)});
        }
        pts = aps;
        cirs.assign(n, vector<pair<double, int>>());
        e1.resize(n);
        e2.resize(n);
        for (i = 0; i < n; i++) {
            Vec ref = fabs(aps[i].z) < 0.9 ? Vec{0.0, 0.0, 1.0} : Vec{1.0, 0.0, 0.0};
            e1[i] = unitVal(crossVal(aps[i], ref));
            e2[i] = crossVal(aps[i], e1[i]);
        }
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                Vec cr = crossVal(aps[i], aps[j]);
                double clen = normVal(cr);
                double den = 1.0 + dotVal(aps[i], aps[j]);
                if (clen < epsVal || fabs(den) < epsVal) continue;
                Vec p0 = (aps[i] + aps[j]) * (cs / den);
                h2 = 1.0 - dotVal(p0, p0);
                if (h2 < -epsVal) continue;
                h = sqrt(max(0.0, h2));
                Vec dir = cr * (1.0 / clen);
                Vec p1 = p0 + dir * h, p2 = p0 - dir * h;
                int id1 = pts.size(), id2;
                pts.push_back(p1);
                cirs[i].push_back({fixAng(atan2(dotVal(p1, e2[i]), dotVal(p1, e1[i]))), id1});
                cirs[j].push_back({fixAng(atan2(dotVal(p1, e2[j]), dotVal(p1, e1[j]))), id1});
                if (h > epsVal) {
                    id2 = pts.size();
                    pts.push_back(p2);
                    cirs[i].push_back({fixAng(atan2(dotVal(p2, e2[i]), dotVal(p2, e1[i]))), id2});
                    cirs[j].push_back({fixAng(atan2(dotVal(p2, e2[j]), dotVal(p2, e1[j]))), id2});
                }
            }
        }
        m = pts.size();
        geo.assign(m, vector<double>(m, infVal));
        for (i = 0; i < m; i++) geo[i][i] = 0.0;
        for (i = 0; i < m; i++) {
            for (j = i + 1; j < m; j++) {
                if (greatArc(pts[i], pts[j], aps, cs)) {
                    dval = earthR * acos(max(-1.0, min(1.0, dotVal(pts[i], pts[j]))));
                    geo[i][j] = geo[j][i] = dval;
                }
            }
        }
        for (i = 0; i < n; i++) {
            sort(cirs[i].begin(), cirs[i].end());
            k = cirs[i].size();
            for (j = 0; j < k; j++) {
                int a = cirs[i][j].second;
                int b = cirs[i][(j + 1) % k].second;
                double st = cirs[i][j].first;
                double ed = j + 1 < k ? cirs[i][j + 1].first : cirs[i][0].first + 2.0 * pi;
                if (a == b || ed - st < epsVal) continue;
                if (cirArc(aps[i], e1[i], e2[i], cs, sn, st, ed, aps)) {
                    dval = earthR * sn * (ed - st);
                    if (geo[a][b] > dval) geo[a][b] = geo[b][a] = dval;
                }
            }
        }
        dist.assign(n, vector<double>(n, infVal));
        for (i = 0; i < n; i++) {
            vector<double> cur = dijk(i, geo);
            for (j = 0; j < n; j++) dist[i][j] = cur[j];
        }
        cin >> q;
        cout << "Case " << cas++ << ":\n";
        while (q--) {
            cin >> s >> t >> c;
            s--;
            t--;
            vector<vector<double>> air(n, vector<double>(n, infVal));
            for (i = 0; i < n; i++) {
                air[i][i] = 0.0;
                for (j = 0; j < n; j++)
                    if (dist[i][j] <= c + 1e-7) air[i][j] = dist[i][j];
            }
            vector<double> ans = dijk(s, air);
            if (ans[t] >= infVal / 2.0) cout << "impossible\n";
            else cout << fixed << setprecision(3) << ans[t] << "\n";
        }
    }
    return 0;
}
