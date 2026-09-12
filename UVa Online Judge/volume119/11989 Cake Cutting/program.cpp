#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1.0);

struct Point {
    double x, y;
};

struct Line {
    Point p, v;
    double ang;
};

map<double, Line> mp;
double sumCross;

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point sub(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

Point add(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point mul(Point a, double k) {
    return {a.x * k, a.y * k};
}

bool inside(Line l, Point p) {
    return cross(l.v, sub(p, l.p)) >= -eps;
}

bool sameDir(Line a, Line b) {
    return fabs(cross(a.v, b.v)) < eps && a.v.x * b.v.x + a.v.y * b.v.y > 0;
}

Point inter(Line a, Line b) {
    Point d = sub(b.p, a.p);
    double t = cross(d, b.v) / cross(a.v, b.v);
    return add(a.p, mul(a.v, t));
}

map<double, Line>::iterator getPre(map<double, Line>::iterator it) {
    if (it == mp.begin()) return prev(mp.end());
    return prev(it);
}

map<double, Line>::iterator getNex(map<double, Line>::iterator it) {
    ++it;
    if (it == mp.end()) return mp.begin();
    return it;
}

void rebuild() {
    sumCross = 0;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        auto nx = getNex(it);
        auto nn = getNex(nx);
        Point a = inter(it->second, nx->second);
        Point b = inter(nx->second, nn->second);
        sumCross += cross(a, b);
    }
}

void insertLine(map<double, Line>::iterator it) {
    auto pr = getPre(it);
    auto nx = getNex(it);
    auto pp = getPre(pr);
    auto nn = getNex(nx);
    Point a = inter(pp->second, pr->second);
    Point b = inter(pr->second, nx->second);
    Point c = inter(nx->second, nn->second);
    Point d = inter(pr->second, it->second);
    Point e = inter(it->second, nx->second);
    sumCross -= cross(a, b) + cross(b, c);
    sumCross += cross(a, d) + cross(d, e) + cross(e, c);
}

void eraseLine(map<double, Line>::iterator it) {
    auto pr = getPre(it);
    auto nx = getNex(it);
    auto pp = getPre(pr);
    auto nn = getNex(nx);
    Point a = inter(pp->second, pr->second);
    Point b = inter(pr->second, it->second);
    Point c = inter(it->second, nx->second);
    Point d = inter(nx->second, nn->second);
    Point e = inter(pr->second, nx->second);
    sumCross -= cross(a, b) + cross(b, c) + cross(c, d);
    sumCross += cross(a, e) + cross(e, d);
    mp.erase(it);
}

void changeLine(map<double, Line>::iterator it, Line l) {
    auto pr = getPre(it);
    auto nx = getNex(it);
    auto pp = getPre(pr);
    auto nn = getNex(nx);
    Point a = inter(pp->second, pr->second);
    Point b = inter(pr->second, it->second);
    Point c = inter(it->second, nx->second);
    Point d = inter(nx->second, nn->second);
    it->second = l;
    Point e = inter(pr->second, it->second);
    Point f = inter(it->second, nx->second);
    sumCross -= cross(a, b) + cross(b, c) + cross(c, d);
    sumCross += cross(a, e) + cross(e, f) + cross(f, d);
}

bool addCut(Line l) {
    auto pos = mp.lower_bound(l.ang);
    auto nx = pos == mp.end() ? mp.begin() : pos;
    auto pr = getPre(nx);
    map<double, Line>::iterator it;
    if (sameDir(pr->second, l)) {
        if (inside(l, pr->second.p)) return true;
        changeLine(pr, l);
        it = pr;
    } else if (sameDir(nx->second, l)) {
        if (inside(l, nx->second.p)) return true;
        changeLine(nx, l);
        it = nx;
    } else {
        Point p = inter(pr->second, nx->second);
        if (inside(l, p)) return true;
        it = mp.insert({l.ang, l}).first;
        insertLine(it);
    }
    while (true) {
        auto a = getPre(it);
        auto b = getPre(a);
        Point p = inter(b->second, a->second);
        if (inside(it->second, p)) break;
        if (mp.size() == 3) return false;
        eraseLine(a);
    }
    while (true) {
        auto a = getNex(it);
        auto b = getNex(a);
        Point p = inter(a->second, b->second);
        if (inside(it->second, p)) break;
        if (mp.size() == 3) return false;
        eraseLine(a);
    }
    return sumCross > eps;
}

Line makeLine(double x1, double y1, double x2, double y2) {
    Point p = {x1, y1};
    Point v = {x2 - x1, y2 - y1};
    double ang = atan2(v.y, v.x);
    if (ang < 0) ang += 2 * pi;
    return {p, v, ang};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double w, h;
    while (cin >> n >> w >> h) {
        mp.clear();
        sumCross = 0;
        Line a = makeLine(0, 0, w, 0);
        Line b = makeLine(w, 0, w, h);
        Line c = makeLine(w, h, 0, h);
        Line d = makeLine(0, h, 0, 0);
        mp[a.ang] = a;
        mp[b.ang] = b;
        mp[c.ang] = c;
        mp[d.ang] = d;
        rebuild();
        bool empty = false;
        for (int i = 0; i < n; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (!empty) {
                Line l = makeLine(x1, y1, x2, y2);
                if (!addCut(l)) empty = true;
            }
            double ans = empty ? 0.0 : max(0.0, sumCross / 2.0);
            cout << fixed << setprecision(3) << ans << '\n';
        }
    }
    return 0;
}
