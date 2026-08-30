#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

struct Point {
    double x, y;
};

Point operator + (const Point& a, const Point& b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator - (const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

Point operator * (const Point& a, double k) {
    return {a.x * k, a.y * k};
}

double crossProduct(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double dotProduct(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

bool isInside(const Point& p, double a, double b, double c) {
    return a * p.x + b * p.y <= c + eps;
}

Point getIntersection(const Point& s, const Point& e, double a, double b, double c) {
    Point d = e - s;
    double t = (c - a * s.x - b * s.y) / (a * d.x + b * d.y);
    return s + d * t;
}

vector<Point> clipPolygon(const vector<Point>& polygon, double a, double b, double c) {
    vector<Point> result;
    int size = polygon.size();
    for (int i = 0; i < size; i++) {
        Point start = polygon[i], end = polygon[(i + 1) % size];
        bool startInside = isInside(start, a, b, c), endInside = isInside(end, a, b, c);
        if (startInside && endInside)
            result.push_back(end);
        else if (startInside && !endInside) {
            result.push_back(getIntersection(start, end, a, b, c));
        } else if (!startInside && endInside) {
            result.push_back(getIntersection(start, end, a, b, c));
            result.push_back(end);
        }
    }
    return result;
}

double getArea(const vector<Point>& polygon) {
    if (polygon.size() < 3)
        return 0.0;
    double area = 0.0;
    int size = polygon.size();
    for (int i = 0; i < size; i++)
        area += crossProduct(polygon[i], polygon[(i + 1) % size]);
    return fabs(area) * 0.5;
}

double getPlayerArea(const vector<Point>& players, int current, double x0, double y0, double xf, double yf) {
    vector<Point> polygon = {{x0, y0}, {xf, y0}, {xf, yf}, {x0, yf}};
    int size = players.size();
    for (int i = 0; i < size; i++) {
        if (i == current)
            continue;
        Point currentPlayer = players[current], otherPlayer = players[i];
        double a = 2.0 * (otherPlayer.x - currentPlayer.x), b = 2.0 * (otherPlayer.y - currentPlayer.y);
        double c = otherPlayer.x * otherPlayer.x + otherPlayer.y * otherPlayer.y - currentPlayer.x * currentPlayer.x - currentPlayer.y * currentPlayer.y;
        if (polygon.empty())
            break;
        polygon = clipPolygon(polygon, a, b, c);
    }
    return getArea(polygon);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n;
        double x0, y0, xf, yf;
        cin >> x0 >> y0 >> xf >> yf;
        cin >> n;
        vector<Point> players(2 * n);
        for (int i = 0; i < 2 * n; i++)
            cin >> players[i].x >> players[i].y;
        double gryffindorArea = 0.0, slytherinArea = 0.0;
        for (int i = 0; i < n; i++)
            gryffindorArea += getPlayerArea(players, i, x0, y0, xf, yf);
        for (int i = n; i < 2 * n; i++)
            slytherinArea += getPlayerArea(players, i, x0, y0, xf, yf);
        if (gryffindorArea > slytherinArea)
            cout << "Gryffindor\n";
        else
            cout << "Slytherin\n";
    }
    return 0;
}
