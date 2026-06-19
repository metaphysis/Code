// Crossing Prisms
// UVa ID: 1338
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct Point { double x, z; };

// 射线法判断点是否在多边形内部（内部在边的右侧）
bool inside(double x, double z, const vector<Point> &p) {
    int n = p.size() - 1, cnt = 0;
    for (int i = 0; i < n; ++i) {
        double z1 = p[i].z, z2 = p[i + 1].z;
        if (fabs(z1 - z2) < 1e-12) continue;
        double zmin = min(z1, z2), zmax = max(z1, z2);
        if (z > zmin + 1e-12 && z < zmax - 1e-12) {
            double xi = p[i].x + (p[i + 1].x - p[i].x) * (z - z1) / (z2 - z1);
            if (xi >= x - 1e-12) ++cnt;
        }
    }
    return cnt % 2 == 1;
}

// 计算水平线 z 与多边形交集的闭包总长度 L
double lengthAtZ(double z, const vector<Point> &p) {
    int n = p.size() - 1;
    vector<double> xs;
    for (int i = 0; i < n; ++i) {
        double z1 = p[i].z, z2 = p[i + 1].z;
        if (fabs(z1 - z2) < 1e-12) {
            if (fabs(z1 - z) < 1e-12) {
                xs.push_back(p[i].x);
                xs.push_back(p[i + 1].x);
            }
        } else {
            double zmin = min(z1, z2), zmax = max(z1, z2);
            if (z >= zmin - 1e-12 && z <= zmax + 1e-12) {
                double x = p[i].x + (p[i + 1].x - p[i].x) * (z - z1) / (z2 - z1);
                xs.push_back(x);
            }
        }
    }
    if (xs.empty()) return 0.0;
    sort(xs.begin(), xs.end());
    double L = 0.0;
    for (size_t i = 0; i + 1 < xs.size(); ++i) {
        if (fabs(xs[i] - xs[i + 1]) < 1e-12) { ++i; continue; }
        double xmid = (xs[i] + xs[i + 1]) * 0.5;
        if (inside(xmid, z, p)) L += xs[i + 1] - xs[i], ++i;
    }
    return L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(4);
    int n;
    while (cin >> n && n) {
        vector<Point> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].z;
        p.push_back(p[0]);

        vector<double> zs;
        for (auto &pt : p) zs.push_back(pt.z);
        sort(zs.begin(), zs.end());
        zs.erase(unique(zs.begin(), zs.end(), [](double a, double b) { return fabs(a - b) < 1e-12; }), zs.end());
        int m = zs.size();

        vector<double> mEdge(n, 0.0), cEdge(n, 0.0);
        for (int i = 0; i < n; ++i)
            if (fabs(p[i].z - p[i + 1].z) > 1e-12) {
                double dz = p[i + 1].z - p[i].z, dx = p[i + 1].x - p[i].x;
                mEdge[i] = dx / dz;
                cEdge[i] = p[i].x - mEdge[i] * p[i].z;
            }

        double sideArea = 0.0;
        for (int k = 0; k < m - 1; ++k) {
            double za = zs[k], zb = zs[k + 1], zm = (za + zb) * 0.5;
            vector<pair<double, int>> inters;
            for (int i = 0; i < n; ++i) {
                double z1 = p[i].z, z2 = p[i + 1].z;
                if (fabs(z1 - z2) < 1e-12) continue;
                double zmin = min(z1, z2), zmax = max(z1, z2);
                if (zm > zmin + 1e-12 && zm < zmax - 1e-12) {
                    double x = p[i].x + (p[i + 1].x - p[i].x) * (zm - z1) / (z2 - z1);
                    inters.emplace_back(x, i);
                }
            }
            sort(inters.begin(), inters.end());
            double A = 0.0, B = 0.0, sumSqrt = 0.0, Lmid = 0.0;
            vector<bool> used(inters.size(), false);
            for (size_t i = 0; i + 1 < inters.size(); ++i) {
                if (used[i]) continue;
                double xmid = (inters[i].first + inters[i + 1].first) * 0.5;
                if (inside(xmid, zm, p)) {
                    int iL = inters[i].second, iR = inters[i + 1].second;
                    Lmid += inters[i + 1].first - inters[i].first;
                    A += mEdge[iR] - mEdge[iL];
                    B += cEdge[iR] - cEdge[iL];
                    sumSqrt += sqrt(1 + mEdge[iL] * mEdge[iL]) + sqrt(1 + mEdge[iR] * mEdge[iR]);
                    used[i] = used[i + 1] = true; ++i;
                }
            }
            if (Lmid > 1e-14) {
                double integ = 0.5 * A * (zb * zb - za * za) + B * (zb - za);
                sideArea += 2.0 * sumSqrt * integ;
            }
        }

        double horizArea = 0.0;
        double eps = 1e-8;
        for (int i = 0; i < m; ++i) {
            double z = zs[i];
            double L_left = lengthAtZ(z - eps, p);
            double L_right = lengthAtZ(z + eps, p);
            horizArea += fabs(L_right * L_right - L_left * L_left);
        }

        cout << sideArea + horizArea << '\n';
    }
    return 0;
}
