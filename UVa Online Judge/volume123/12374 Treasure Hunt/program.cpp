#include <bits/stdc++.h>
using namespace std;

const long double Inf = 1e100L;
const long double Eps = 1e-18L;

struct Point {
    long double x, y;
    Point operator + (const Point &p) const {
        return {x + p.x, y + p.y};
    }
    Point operator - (const Point &p) const {
        return {x - p.x, y - p.y};
    }
    Point operator * (long double k) const {
        return {x * k, y * k};
    }
};

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double len(Point a) {
    return sqrtl(dot(a, a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Point p[4], c[4];
    while (true) {
        bool end = true;
        for (int i = 0; i < 4; ++i) {
            if (!(cin >> p[i].x >> p[i].y))
                return 0;
            if (fabsl(p[i].x) > Eps || fabsl(p[i].y) > Eps)
                end = false;
        }
        for (int i = 0; i < 4; ++i) {
            cin >> c[i].x >> c[i].y;
            if (fabsl(c[i].x) > Eps || fabsl(c[i].y) > Eps)
                end = false;
        }
        if (end)
            break;
        Point center = {(c[0].x + c[1].x + c[2].x + c[3].x) / 4.0L, (c[0].y + c[1].y + c[2].y + c[3].y) / 4.0L};
        Point sum = {0.0L, 0.0L};
        for (int i = 0; i < 4; ++i)
            sum = sum + p[i];
        Point need = center * 4.0L - sum;
        long double total = len(need);
        Point dir = {0.0L, 0.0L};
        if (total > Eps)
            dir = need * (1.0L / total);
        Point ex = c[1] - c[0], ey = c[3] - c[0];
        long double width = len(ex), height = len(ey);
        ex = ex * (1.0L / width);
        ey = ey * (1.0L / height);
        long double du = dot(dir, ex), dv = dot(dir, ey);
        long double remain = total;
        for (int i = 0; i < 4; ++i) {
            if (remain <= Eps)
                break;
            long double a = dot(p[i] - c[0], ex), b = dot(p[i] - c[0], ey);
            long double limX = Inf, limY = Inf;
            if (du > Eps)
                limX = (width - a) / du;
            else if (du < -Eps)
                limX = -a / du;
            if (dv > Eps)
                limY = (height - b) / dv;
            else if (dv < -Eps)
                limY = -b / dv;
            long double limit = min(limX, limY);
            long double move = min(remain, limit);
            p[i] = p[i] + dir * move;
            remain -= move;
        }
        cout << fixed << setprecision(12);
        for (int i = 0; i < 4; ++i)
            cout << (double)p[i].x << ' ' << (double)p[i].y << '\n';
        cout << '\n';
    }
    return 0;
}
