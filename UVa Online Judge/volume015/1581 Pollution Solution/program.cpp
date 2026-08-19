#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x;
    long double y;
};
Point operator +(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
}
Point operator -(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}
Point operator *(const Point &a, long double value) {
    return {a.x * value, a.y * value};
}
long double getCross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
long double getDot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
long double getLengthSquare(const Point &a) {
    return getDot(a, a);
}

long double getEdgeContribution(const Point &a, const Point &b, long double radius) {
    const long double epsilon = 1e-12L;
    Point direction = b - a;
    long double qa = getLengthSquare(direction);
    long double qb = 2.0L * getDot(a, direction);
    long double qc = getLengthSquare(a) - radius * radius;
    vector<long double> parameters;
    parameters.push_back(0.0L);
    parameters.push_back(1.0L);
    long double discriminant = qb * qb - 4.0L * qa * qc;
    if (discriminant >= -epsilon) {
        discriminant = max(0.0L, discriminant);
        long double root = sqrtl(discriminant);
        long double t1 = (-qb - root) / (2.0L * qa);
        long double t2 = (-qb + root) / (2.0L * qa);
        if (t1 > epsilon && t1 < 1.0L - epsilon) parameters.push_back(t1);
        if (t2 > epsilon && t2 < 1.0L - epsilon) parameters.push_back(t2);
    }
    sort(parameters.begin(), parameters.end());
    vector<long double> uniqueParameters;
    for (long double value : parameters)
        if (uniqueParameters.empty() || fabsl(value - uniqueParameters.back()) > epsilon) uniqueParameters.push_back(value);
    long double result = 0.0L;
    for (int i = 0; i + 1 < static_cast<int>(uniqueParameters.size()); i++) {
        long double left = uniqueParameters[i];
        long double right = uniqueParameters[i + 1];
        Point start = a + direction * left;
        Point end = a + direction * right;
        Point middle = a + direction * ((left + right) / 2.0L);
        if (getLengthSquare(middle) <= radius * radius + epsilon)
            result += getCross(start, end) / 2.0L;
        else
            result += radius * radius * atan2l(getCross(start, end), getDot(start, end)) / 2.0L;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long double radius;
    cout << fixed << setprecision(10);
    while (cin >> n >> radius) {
        vector<Point> polygon(n);
        for (Point &point : polygon) cin >> point.x >> point.y;
        long double area = 0.0L;
        for (int i = 0; i < n; i++)
            area += getEdgeContribution(polygon[i], polygon[(i + 1) % n], radius);
        cout << fabsl(area) << '\n';
    }
    return 0;
}
