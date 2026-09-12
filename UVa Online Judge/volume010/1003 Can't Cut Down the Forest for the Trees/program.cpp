#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

using Point = pair<double, double>;
vector<Point> segments;

struct Tree {
    double x, y, r;
    double X, H;
    void setValue(int xx, int yy, int hh, int diameter) {
        x = (double)xx, y = (double)yy, H = (double)hh, r = diameter / 2.0;
        X = sqrt(r * r + H * H);
    }
} trees[110];

double squareValue(double value) { return value * value; }

double treeDistance(int i, int j) {
    return sqrt(squareValue(trees[i].x - trees[j].x) + squareValue(trees[i].y - trees[j].y));
}

double commonTangent(int i, int j) {
    return sqrt(squareValue(trees[i].x - trees[j].x) + squareValue(trees[i].y - trees[j].y) - squareValue(trees[i].r + trees[j].r));
}

double normalizeDegree(double degree) {
    return degree > 0.0 ? degree : 360.0 + degree;
}

double treeDirection(int i, int j) {
    double degree = atan2(trees[j].y - trees[i].y, trees[j].x - trees[i].x) * 180.0 / PI;
    return normalizeDegree(degree);
}

bool crossesZero(double degree, double halfWidth) {
    return degree + halfWidth > 360.0 || degree - halfWidth < 0.0;
}

void addTreeInterval(double degree, double theta) {
    if (crossesZero(degree, theta)) {
        if (degree + theta > 360.0) {
            segments.emplace_back(degree - theta, 360.0);
            segments.emplace_back(0.0, degree + theta - 360.0);
        } else if (degree - theta < 0.0) {
            segments.emplace_back(0.0, degree + theta);
            segments.emplace_back(360.0 + degree - theta, 360.0);
        }
    } else {
        segments.emplace_back(degree - theta, degree + theta);
    }
}

void checkWall(int i, double x1, double x2, double y1, double y2) {
    double D;
    D = trees[i].x - x1;
    if (D <= trees[i].X) {
        double theta = acos(D / trees[i].X) * 180.0 / PI;
        double alpha = acos(trees[i].H / trees[i].X) * 180.0 / PI;
        segments.emplace_back(180.0 - theta - alpha, 180.0 + theta + alpha);
    }
    D = trees[i].y - y1;
    if (D <= trees[i].X) {
        double theta = acos(D / trees[i].X) * 180.0 / PI;
        double alpha = acos(trees[i].H / trees[i].X) * 180.0 / PI;
        segments.emplace_back(270.0 - theta - alpha, 270.0 + theta + alpha);
    }
    D = x2 - trees[i].x;
    if (D <= trees[i].X) {
        double theta = acos(D / trees[i].X) * 180.0 / PI;
        double alpha = acos(trees[i].H / trees[i].X) * 180.0 / PI;
        segments.emplace_back(0.0, theta + alpha);
        segments.emplace_back(360.0 - theta - alpha, 360.0);
    }
    D = y2 - trees[i].y;
    if (D <= trees[i].X) {
        double theta = acos(D / trees[i].X) * 180.0 / PI;
        double alpha = acos(trees[i].H / trees[i].X) * 180.0 / PI;
        segments.emplace_back(90.0 - theta - alpha, 90.0 + theta + alpha);
    }
}

void checkTree(int i, int j) {
    double D = treeDistance(i, j) - trees[j].r;
    if (D > trees[i].X) return;
    if (trees[i].H > D) {
        double h = min(trees[i].H, commonTangent(i, j));
        double z = sqrt(squareValue(h) + squareValue(trees[i].r));
        double gamma = atan(h / trees[i].r) * 180.0 / PI;
        double alpha = acos((squareValue(z) + squareValue(D + trees[j].r) - squareValue(trees[j].r)) / (2.0 * z * (D + trees[j].r))) * 180.0 / PI;
        double theta = 90.0 - (gamma - alpha);
        addTreeInterval(treeDirection(i, j), theta);
    } else if (trees[i].X > D) {
        double theta = acos(trees[i].H / D);
        addTreeInterval(treeDirection(i, j), theta);
    }
}

int main() {
    int forestNumber = 1;
    while (true) {
        int X1, Y1, X2, Y2, n;
        scanf("%d %d %d %d %d", &X1, &Y1, &X2, &Y2, &n);
        if (X1 == 0 && Y1 == 0 && X2 == 0 && Y2 == 0 && n == 0) break;
        double x1 = (double)X1, y1 = (double)Y1;
        double x2 = (double)X2, y2 = (double)Y2;
        int originalCount = n;
        for (int i = 0; i < n; ++i) {
            int x, y, diameter, height;
            scanf("%d %d %d %d", &x, &y, &diameter, &height);
            trees[i].setValue(x, y, height, diameter);
        }
        while (n > 0) {
            int deleted = -1;
            for (int i = 0; i < n; ++i) {
                checkWall(i, x1, x2, y1, y2);
                for (int j = 0; j < n; ++j) {
                    if (i != j) checkTree(i, j);
                }
                sort(segments.begin(), segments.end());
                double rightmost = 0.0;
                for (const auto& interval : segments) {
                    if (rightmost < interval.first) {
                        deleted = i;
                        break;
                    }
                    rightmost = max(rightmost, interval.second);
                }
                if (segments.empty()) deleted = i;
                else {
                    int last = static_cast<int>(segments.size()) - 1;
                    if (segments[0].first > 0.0 && segments[last].second < 360.0) deleted = i;
                }
                segments.clear();
                if (deleted != -1) break;
            }
            if (deleted == -1) break;
            --n;
            for (int i = deleted; i < n; ++i) trees[i] = trees[i + 1];
        }
        printf("Forest %d\n", forestNumber++);
        printf("%d tree(s) can be cut\n\n", originalCount - n);
    }
    return 0;
}
