#include <bits/stdc++.h>
using namespace std;

const long double Eps = 1e-12L;
const long double InEps = 1e-9L;

struct Receiver {
    long double x, y;
    long long p;
};

struct Equation {
    long double a, b, c, d;
};

Equation GetEquation(const Receiver &first, const Receiver &second) {
    Equation result;
    result.a = first.p - second.p;
    result.b = -2.0L * (first.p * first.x - second.p * second.x);
    result.c = -2.0L * (first.p * first.y - second.p * second.y);
    result.d = first.p * (first.x * first.x + first.y * first.y) - second.p * (second.x * second.x + second.y * second.y);
    return result;
}

void AddPoint(vector<pair<long double, long double> > &points, long double x, long double y) {
    if (x < -InEps || x > 1000.0L + InEps || y < -InEps || y > 1000.0L + InEps)
        return;
    x = max(0.0L, min(1000.0L, x));
    y = max(0.0L, min(1000.0L, y));
    for (pair<long double, long double> point : points)
        if (fabsl(point.first - x) < 1e-8L && fabsl(point.second - y) < 1e-8L)
            return;
    points.push_back(make_pair(x, y));
}

void AddLineCircle(vector<pair<long double, long double> > &points, long double ux, long double uy, long double v, const Equation &circle) {
    long double norm = sqrtl(ux * ux + uy * uy);
    if (norm < Eps)
        return;
    long double centerX = -circle.b / (2.0L * circle.a), centerY = -circle.c / (2.0L * circle.a);
    long double radiusSquare = (circle.b * circle.b + circle.c * circle.c) / (4.0L * circle.a * circle.a) - circle.d / circle.a;
    long double distance = (ux * centerX + uy * centerY + v) / norm;
    long double footX = centerX - ux * distance / norm, footY = centerY - uy * distance / norm;
    long double heightSquare = radiusSquare - distance * distance;
    if (heightSquare < -Eps)
        return;
    if (heightSquare < 0.0L)
        heightSquare = 0.0L;
    long double height = sqrtl(heightSquare), dirX = -uy / norm, dirY = ux / norm;
    AddPoint(points, footX + dirX * height, footY + dirY * height);
    if (height > Eps)
        AddPoint(points, footX - dirX * height, footY - dirY * height);
}

void SolveCase(Receiver receivers[3]) {
    Equation first = GetEquation(receivers[0], receivers[1]), second = GetEquation(receivers[0], receivers[2]);
    vector<pair<long double, long double> > points;
    bool firstLine = fabsl(first.a) < Eps, secondLine = fabsl(second.a) < Eps;
    if (firstLine && secondLine) {
        long double determinant = first.b * second.c - second.b * first.c;
        if (fabsl(determinant) >= Eps) {
            long double x = (first.c * second.d - second.c * first.d) / determinant;
            long double y = (second.b * first.d - first.b * second.d) / determinant;
            AddPoint(points, x, y);
        }
    } else if (firstLine) {
        AddLineCircle(points, first.b, first.c, first.d, second);
    } else if (secondLine) {
        AddLineCircle(points, second.b, second.c, second.d, first);
    } else {
        long double ux = first.b / first.a - second.b / second.a;
        long double uy = first.c / first.a - second.c / second.a;
        long double v = first.d / first.a - second.d / second.a;
        AddLineCircle(points, ux, uy, v, first);
    }
    sort(points.begin(), points.end(), [](const pair<long double, long double> &left, const pair<long double, long double> &right) {
        if (fabsl(left.first - right.first) > 1e-8L)
            return left.first < right.first;
        return left.second < right.second;
    });
    cout << points.size();
    cout << fixed << setprecision(2);
    for (pair<long double, long double> point : points) {
        long double x = fabsl(point.first) < 0.0005L ? 0.0L : point.first;
        long double y = fabsl(point.second) < 0.0005L ? 0.0L : point.second;
        cout << " " << (double)x << " " << (double)y;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        Receiver receivers[3];
        for (int i = 0; i < 3; ++i)
            cin >> receivers[i].x >> receivers[i].y >> receivers[i].p;
        SolveCase(receivers);
    }
    return 0;
}
