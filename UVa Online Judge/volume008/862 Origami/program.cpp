#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-6;

struct Point {
    long double x, y;
};

struct Fold {
    Point a, b;
};

int stepCount;
Fold folds[8];

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point reflectPoint(Point p, Fold f) {
    long double dx = f.b.x - f.a.x, dy = f.b.y - f.a.y;
    long double len = dx * dx + dy * dy;
    long double t = ((p.x - f.a.x) * dx + (p.y - f.a.y) * dy) / len;
    Point h = {f.a.x + t * dx, f.a.y + t * dy};
    return {2 * h.x - p.x, 2 * h.y - p.y};
}

int countLayer(int index, Point p) {
    if (index < 0) {
        if (p.x > eps && p.x < 100 - eps && p.y > eps && p.y < 100 - eps) return 1;
        return 0;
    }
    long double side = cross(folds[index].a, folds[index].b, p);
    if (fabsl(side) <= eps || side < -eps) return 0;
    Point other = reflectPoint(p, folds[index]);
    return countLayer(index - 1, p) + countLayer(index - 1, other);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseCount;
    cin >> caseCount;
    for (int caseIndex = 0; caseIndex < caseCount; caseIndex++) {
        cin >> stepCount;
        for (int i = 0; i < stepCount; i++)
            cin >> folds[i].a.x >> folds[i].a.y >> folds[i].b.x >> folds[i].b.y;
        int queryCount;
        cin >> queryCount;
        if (caseIndex > 0) cout << '\n';
        for (int i = 0; i < queryCount; i++) {
            Point p;
            cin >> p.x >> p.y;
            cout << countLayer(stepCount - 1, p) << '\n';
        }
    }
    return 0;
}
