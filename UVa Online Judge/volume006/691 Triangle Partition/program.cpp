// Triangle Partition
// UVa ID: 691
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 8.530s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct point { double x, y; };

point operator-(const point& a, const point& b) { return {a.x - b.x, a.y - b.y}; }
point operator+(const point& a, const point& b) { return {a.x + b.x, a.y + b.y}; }
point operator*(const point& a, double k) { return {a.x * k, a.y * k}; }
point operator/(const point& a, double k) { return {a.x / k, a.y / k}; }

double cross(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }

inline bool pointInTriangle(point& P, point& T1, point& T2, point& T3) {
    double d1 = cross(T2 - T1, P - T1);
    double d2 = cross(T3 - T2, P - T2);
    double d3 = cross(T1 - T3, P - T3);
    bool hasPos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
    bool hasNeg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    return !(hasPos && hasNeg);
}

typedef vector<point> polygon;

int n;
polygon pts;

bool countTriangles(point& Q, point& A, point& B, point& C) {
    int c1 = 0, c2 = 0, c3 = 0;
    for (auto& p : pts) {
        if (pointInTriangle(p, Q, B, C)) c1++;
        if (pointInTriangle(p, Q, C, A)) c2++;
        if (pointInTriangle(p, Q, A, B)) c3++;
    }
    return c1 == c2 && c2 == c3;
}

void intersectLines(point& p1, point& p2, point& p3, point& p4, point& q) {
    point d1 = p2 - p1, d2 = p4 - p3, r = p3 - p1;
    double t = cross(r, d2) / cross(d1, d2);
    q = p1 + d1 * t;
}

void solve0() {
    point P[3] = {{0.0, 0.0}, {1000.0, 0.0}, {0.0, 1000.0}};
    polygon ps[3];
    for (int i = 0; i < 3; i++) {
        ps[i].insert(ps[i].begin(), pts.begin(), pts.end());
        sort(ps[i].begin(), ps[i].end(), [&](const point& a, const point& b) {
            return atan2(a.y - P[i].y, a.x - P[i].x) < atan2(b.y - P[i].y, b.x - P[i].x);
        });
    }
    int needed = (n + 2) / 3;
    int start = needed - 1, end = n - needed;
    while (true) {
        int a = rand() % 3, b = (a + 1) % 3;
        bool found = false;
        for (int i = start; i < end; i++) {
            double fa = (rand() % 10000) / 10000.0;
            point m1 = ps[a][i] + (ps[a][i + 1] - ps[a][i]) * fa;
            for (int j = start; j < end; j++) {
                double fb = (rand() % 10000) / 10000.0;
                point m2 = ps[b][j] + (ps[b][j + 1] - ps[b][j]) * fb;
                point Q;
                intersectLines(P[a], m1, P[b], m2, Q);
                if (countTriangles(Q, P[0], P[1], P[2])) {
                    cout << Q.x << " " << Q.y << "\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found) break;
    }
}

polygon getCandidates(point& V, bool includeAll) {
    polygon sorted(pts);
    sort(sorted.begin(), sorted.end(), [&](const point& a, const point& b) {
        return atan2(a.y - V.y, a.x - V.x) < atan2(b.y - V.y, b.x - V.x);
    });
    int needed = (n + 2) / 3;
    int start = needed - 1, end = n - needed;
    polygon r;
    for (int i = start; i <= end; i++) {
        r.push_back(sorted[i]);
        if (includeAll)
            for (int j = i + 1; j <= end; j++)
                r.push_back((sorted[i] + sorted[j]) / 2);
    }
    return r;
}

bool work(polygon& As, polygon& Bs, point& A, point& B, point& C) {
    bool found = false;
    for (auto& dA : As) {
        for (auto& dB : Bs) {
            point Q;
            intersectLines(A, dA, B, dB, Q);
            if (countTriangles(Q, A, B, C)) {
                cout << Q.x << " " << Q.y << "\n";
                found = true;
                break;
            }
        }
        if (found) break;
    }
    return found;
}

void solve1() {
    point A{0.0, 0.0}, B{1000.0, 0.0}, C{0.0, 1000.0};
    polygon As = getCandidates(A, false);
    polygon Bs = getCandidates(B, false);
    polygon Cs = getCandidates(C, false);
    bool found = work(As, Bs, A, B, C);
    if (!found) found = work(As, Cs, A, C, B);
    if (!found) found = work(Bs, Cs, B, C, A);
    assert(found);
}

void solve2() {
    point A{0.0, 0.0}, B{1000.0, 0.0}, C{0.0, 1000.0};
    polygon A1s = getCandidates(A, false);
    polygon B1s = getCandidates(B, false);
    polygon C1s = getCandidates(C, false);
    polygon A2s = getCandidates(A, true);
    polygon B2s = getCandidates(B, true);
    polygon C2s = getCandidates(C, true);
    bool found = work(A1s, B2s, A, B, C);
    if (!found) found = work(A1s, C2s, A, C, B);
    if (!found) found = work(B1s, A2s, B, A, C);
    if (!found) found = work(B1s, C2s, B, C, A);
    if (!found) found = work(C1s, A2s, C, A, B);
    if (!found) found = work(C1s, B2s, C, B, A);
    assert(found);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(7);
    int x, y;
    while (cin >> n, n) {
        pts.clear();
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            pts.push_back({x, y});
        }
        if (n % 3 == 0) solve0();
        if (n % 3 == 1) solve1();
        if (n % 3 == 2) solve2();
    }
    return 0;
}
