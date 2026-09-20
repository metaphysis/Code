#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double getDistance(const Point &a, const Point &b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double normalizeZero(double value) {
    if (fabs(value) < 0.0005) return 0.0;
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNum = 0;
    const double eps = 1e-9;
    while (cin >> n && n != 0) {
        vector<Point> points(n);
        for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
        Point newPoint;
        cin >> newPoint.x >> newPoint.y;
        double minLength = numeric_limits<double>::max();
        int bestIndex = 0;
        for (int i = 0; i < n; i++) {
            int nextIndex = (i + 1) % n;
            double firstLength = getDistance(points[i], newPoint);
            double secondLength = getDistance(points[nextIndex], newPoint);
            double oldLength = getDistance(points[i], points[nextIndex]);
            double currentLength = firstLength + secondLength;
            if (oldLength + eps >= firstLength) currentLength = min(currentLength, secondLength);
            if (oldLength + eps >= secondLength) currentLength = min(currentLength, firstLength);
            if (currentLength + eps < minLength) {
                minLength = currentLength;
                bestIndex = i;
            }
        }
        int nextIndex = (bestIndex + 1) % n;
        if (caseNum > 0) cout << '\n';
        cout << fixed << setprecision(2);
        cout << "Case #" << caseNum << '\n';
        cout << "Disconnect between (" << normalizeZero(points[bestIndex].x) << ',' << normalizeZero(points[bestIndex].y) << ") and (";
        cout << normalizeZero(points[nextIndex].x) << ',' << normalizeZero(points[nextIndex].y) << ").\n";
        cout << "Minimum length of new line: " << normalizeZero(minLength) << '\n';
        caseNum++;
    }
    return 0;
}
