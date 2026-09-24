#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

vector<Point> clipPolygon(const vector<Point>& poly, int a, int b, int c) {
    vector<Point> result;
    if (poly.empty()) return result;
    if (a == 0 && b == 0) {
        if (c > 0) return poly;
        return result;
    }
    Point prev = poly.back();
    long double prevVal = a * prev.x + b * prev.y - c;
    bool prevInside = prevVal <= 0;
    for (const Point& cur : poly) {
        long double curVal = a * cur.x + b * cur.y - c;
        bool curInside = curVal <= 0;
        if (prevInside != curInside) {
            long double ratio = prevVal / (prevVal - curVal);
            result.push_back({prev.x + ratio * (cur.x - prev.x),
                              prev.y + ratio * (cur.y - prev.y)});
        }
        if (curInside) result.push_back(cur);
        prev = cur;
        prevVal = curVal;
        prevInside = curInside;
    }
    return result;
}

long double getArea(const vector<Point>& poly) {
    if (poly.size() < 3) return 0;
    long double area = 0;
    Point prev = poly.back();
    for (const Point& cur : poly) {
        area += prev.x * cur.y - prev.y * cur.x;
        prev = cur;
    }
    return fabsl(area) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int euro, dirham, n, caseNum = 0;
    cout << fixed << setprecision(2);
    while (cin >> euro >> dirham >> n) {
        if (euro == 0 && dirham == 0 && n == 0) break;
        vector<Point> poly;
        poly.push_back({0, 0});
        poly.push_back({euro * 1.0L, 0});
        poly.push_back({euro * 1.0L, dirham * 1.0L});
        poly.push_back({0, dirham * 1.0L});
        for (int i = 0; i < n; ++i) {
            int a, b, c;
            string euroUnit, dirhamUnit;
            char sign, op;
            cin >> a >> euroUnit >> sign >> b >> dirhamUnit >> op >> c;
            if (sign == '-') b = -b;
            if (op == '>') {
                a = -a;
                b = -b;
                c = -c;
            }
            poly = clipPolygon(poly, a, b, c);
        }
        cout << "Case #" << ++caseNum << ": " << getArea(poly) << '\n';
    }
    return 0;
}
