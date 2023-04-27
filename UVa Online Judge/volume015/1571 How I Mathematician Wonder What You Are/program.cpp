// How I Mathematician Wonder What You Are
// UVa ID: 1571
// Verdict: Accepted
// Submission Date: 2023-04-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;
const double EPSILON = 1E-7;

struct point { double x, y; };

struct line {
    point a, b;
    double angle;
};

typedef vector<point> polygon;

double cp(point p1, point p2, point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

bool cw(point p1, point p2, point p3) {  return cp(p1, p2, p3) < -EPSILON; }

bool cmpHalfPlaneLine(line p, line q) {
    if (fabs(p.angle - q.angle) <= EPSILON) return cw(p.a, p.b, q.a);
    return p.angle < q.angle;
}

bool cmpAngle(line p, line q) {  return fabs(p.angle - q.angle) <= EPSILON; }

bool paralleLine(line p, line q) {
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) - (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q) {
    point p1 = p.a;
    double scale = ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

void pointsToLine(point a, point b, line & l) {
    l.a = a, l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
}

polygon halfPlaneIntersection(line *el, int nLine) {
    polygon pg;
    line dl[MAXN];
    sort(el, el + nLine, cmpHalfPlaneLine);
    nLine = unique(el, el + nLine, cmpAngle) - el;
    int bottom = 0, top = 1;
    dl[0] = el[0];
    dl[1] = el[1];
    for (int i = 2; i < nLine; i++) {
        if (paralleLine(dl[top], dl[top - 1]) || paralleLine(dl[bottom], dl[bottom + 1])) return pg;
        while (bottom < top && cw(el[i].a, el[i].b, getIntersection(dl[top], dl[top - 1]))) top--;
        while (bottom < top && cw(el[i].a, el[i].b, getIntersection(dl[bottom], dl[bottom + 1]))) bottom++;
        dl[++top] = el[i];
    }
    while (bottom < top && cw(dl[bottom].a, dl[bottom].b, getIntersection(dl[top], dl[top - 1]))) top--;
    while (bottom < top && cw(dl[top].a, dl[top].b, getIntersection(dl[bottom], dl[bottom + 1]))) bottom++;
    if (top <= (bottom + 1)) return pg;
    for (int i = bottom; i < top; i++) pg.push_back(getIntersection(dl[i], dl[i + 1]));
    if (bottom < (top + 1)) pg.push_back(getIntersection(dl[bottom], dl[top]));
    return pg;
}

int main(int argc, char *argv[]) {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n, cases = 0;
    point vertices[MAXN];
    line el[MAXN];
    while (cin >> n, n) {
        double x, y;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            vertices[i] = (point){x, y};
        }
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            pointsToLine(vertices[i], vertices[j], el[i]);
        }
        polygon pg = halfPlaneIntersection(el, n);
        if (pg.size()) cout << 1;
        else cout << 0;
        cout << '\n';
    }
    return 0;
}
