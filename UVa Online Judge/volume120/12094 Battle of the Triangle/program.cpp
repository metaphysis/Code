#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

struct Point {
    double x, y;
    Point(double xValue = 0, double yValue = 0): x(xValue), y(yValue) {}
};

struct Line {
    int a, b, c;
    bool operator < (const Line &other) const {
        double angle1 = atan2((double)b, (double)a), angle2 = atan2((double)other.b, (double)other.a);
        if (angle1 < 0) angle1 += pi;
        if (angle2 < 0) angle2 += pi;
        return angle1 < angle2;
    }
};

struct PointComparator {
    static Line base;
    bool operator () (const Point &point1, const Point &point2) const {
        double value1 = point1.x * base.a + point1.y * base.b, value2 = point2.x * base.a + point2.y * base.b;
        return value1 < value2;
    }
};

Line PointComparator::base;

Point getIntersection(const Line &line1, const Line &line2) {
    double determinant, x, y;
    determinant = (double)line1.a * line2.b - (double)line2.a * line1.b;
    x = ((double)line1.b * line2.c - (double)line2.b * line1.c) / determinant;
    y = ((double)line2.a * line1.c - (double)line1.a * line2.c) / determinant;
    return Point(x, y);
}

void normalizeLine(Line &line) {
    if (line.a < 0 || (line.a == 0 && line.b < 0)) {
        line.a = -line.a;
        line.b = -line.b;
        line.c = -line.c;
    }
}

int getPart(const vector<Point> &points, const Line &line, const Point &thresholdPoint, const Point &vertex, int index) {
    PointComparator::base = line;
    int position = (int)(lower_bound(points.begin(), points.end(), thresholdPoint, PointComparator()) - points.begin());
    double vertexSide = line.a * vertex.x + line.b * vertex.y + line.c, firstSide = line.a * points.front().x + line.b * points.front().y + line.c, lastSide = line.a * points.back().x + line.b * points.back().y + line.c;
    bool vertexNegative = vertexSide < 0, firstNegative = firstSide < 0, lastNegative = lastSide < 0;
    if (index == 0) {
        if (position) {
            if (vertexNegative != firstNegative) position = (int)points.size() - position;
        } else {
            if (vertexNegative == lastNegative) position = (int)points.size() - position;
        }
    } else {
        if (position) {
            if (vertexNegative == firstNegative) position = (int)points.size() - position;
        } else {
            if (vertexNegative != lastNegative) position = (int)points.size() - position;
        }
    }
    return position;
}

int getDifference(const vector<Point> points[3], Line lines[3], const Point vertices[3]) {
    int parts[3];
    for (int i = 0; i < 3; i++) parts[i] = getPart(points[i], lines[i], vertices[(i + 1) % 3], vertices[i], i);
    return parts[0] - parts[1] - parts[2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int soldierCount, tankCount, queryCount, caseNumber = 0;
    while (cin >> soldierCount >> tankCount >> queryCount) {
        if (soldierCount == 0 && tankCount == 0 && queryCount == 0) break;
        vector<Point> soldiers, tanks, soldier[3], tank[3];
        vector<array<Line, 3>> queries(queryCount);
        for (int i = 0; i < soldierCount; i++) {
            Point point;
            cin >> point.x >> point.y;
            soldiers.push_back(point);
        }
        for (int i = 0; i < tankCount; i++) {
            Point point;
            cin >> point.x >> point.y;
            tanks.push_back(point);
        }
        for (int i = 0; i < queryCount; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> queries[i][j].a >> queries[i][j].b >> queries[i][j].c;
                normalizeLine(queries[i][j]);
            }
            sort(queries[i].begin(), queries[i].end());
        }
        for (int i = 0; i < 3; i++) {
            soldier[i] = soldiers;
            tank[i] = tanks;
            PointComparator::base = queries[0][i];
            sort(soldier[i].begin(), soldier[i].end(), PointComparator());
            sort(tank[i].begin(), tank[i].end(), PointComparator());
        }
        cout << "Battle Field " << ++caseNumber << ":\n";
        for (int i = 0; i < queryCount; i++) {
            Line lines[3];
            Point vertices[3];
            for (int j = 0; j < 3; j++) lines[j] = queries[i][j];
            vertices[0] = getIntersection(lines[1], lines[2]);
            vertices[1] = getIntersection(lines[0], lines[2]);
            vertices[2] = getIntersection(lines[0], lines[1]);
            int soldierDifference = getDifference(soldier, lines, vertices), tankDifference = getDifference(tank, lines, vertices);
            cout << "Query " << i + 1 << ": " << soldierDifference << ' ' << tankDifference << '\n';
        }
    }
    return 0;
}
