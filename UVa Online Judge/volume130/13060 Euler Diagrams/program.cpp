#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);
const long double angleEps = 1e-14L;
const long double pointEps = 1e-12L;

struct Circle {
    long double x, y, r;
};

struct Point {
    long double x, y;
    int firstCircle, secondCircle;
};

int getMask(long double x, long double y, const vector<Circle>& circles) {
    int mask = 0, n = circles.size();
    for (int i = 0; i < n; i++) {
        long double dx = x - circles[i].x, dy = y - circles[i].y;
        long double distSquared = dx * dx + dy * dy, radiusSquared = circles[i].r * circles[i].r;
        if (distSquared <= radiusSquared + pointEps) mask |= 1 << i;
    }
    return mask;
}

int solveCase(int n, const vector<Circle>& circles) {
    vector<vector<long double>> angles(n);
    vector<Point> intersections;
    set<int> zones;
    zones.insert(0);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long double dx = circles[j].x - circles[i].x, dy = circles[j].y - circles[i].y;
            long double distSquared = dx * dx + dy * dy;
            long double radiusSum = circles[i].r + circles[j].r, radiusDiff = circles[i].r - circles[j].r;
            if (distSquared >= radiusSum * radiusSum || distSquared <= radiusDiff * radiusDiff) continue;
            long double dist = sqrtl(distSquared);
            long double along = (circles[i].r * circles[i].r - circles[j].r * circles[j].r + distSquared) / (2.0L * dist);
            long double heightSquared = circles[i].r * circles[i].r - along * along;
            long double height = sqrtl(max(0.0L, heightSquared));
            long double unitX = dx / dist, unitY = dy / dist;
            long double baseX = circles[i].x + along * unitX, baseY = circles[i].y + along * unitY;
            Point firstPoint = {baseX - height * unitY, baseY + height * unitX, i, j};
            Point secondPoint = {baseX + height * unitY, baseY - height * unitX, i, j};
            intersections.push_back(firstPoint);
            intersections.push_back(secondPoint);
            angles[i].push_back(atan2l(firstPoint.y - circles[i].y, firstPoint.x - circles[i].x));
            angles[i].push_back(atan2l(secondPoint.y - circles[i].y, secondPoint.x - circles[i].x));
            angles[j].push_back(atan2l(firstPoint.y - circles[j].y, firstPoint.x - circles[j].x));
            angles[j].push_back(atan2l(secondPoint.y - circles[j].y, secondPoint.x - circles[j].x));
        }
    }
    for (int i = 0; i < n; i++) {
        sort(angles[i].begin(), angles[i].end());
        vector<long double> uniqueAngles;
        for (long double angle : angles[i]) {
            if (uniqueAngles.empty() || fabsl(angle - uniqueAngles.back()) > angleEps) uniqueAngles.push_back(angle);
        }
        if (uniqueAngles.size() > 1 && 2.0L * pi - uniqueAngles.back() + uniqueAngles.front() <= angleEps) uniqueAngles.pop_back();
        if (uniqueAngles.empty()) uniqueAngles.push_back(0.0L);
        int angleCount = uniqueAngles.size();
        for (int j = 0; j < angleCount; j++) {
            long double leftAngle = uniqueAngles[j];
            long double rightAngle = j + 1 < angleCount ? uniqueAngles[j + 1] : uniqueAngles[0] + 2.0L * pi;
            if (rightAngle - leftAngle <= angleEps) continue;
            long double middleAngle = (leftAngle + rightAngle) / 2.0L;
            long double x = circles[i].x + circles[i].r * cosl(middleAngle);
            long double y = circles[i].y + circles[i].r * sinl(middleAngle);
            int mask = getMask(x, y, circles);
            int outsideMask = mask & ~(1 << i), insideMask = outsideMask | (1 << i);
            zones.insert(outsideMask);
            zones.insert(insideMask);
        }
    }
    for (const Point& point : intersections) {
        int mask = getMask(point.x, point.y, circles);
        mask |= 1 << point.firstCircle;
        mask |= 1 << point.secondCircle;
        zones.insert(mask);
    }
    return zones.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int width, height, n;
    while (cin >> width >> height >> n) {
        if (width == 0 && height == 0 && n == 0) break;
        vector<Circle> circles(n);
        for (int i = 0; i < n; i++) cin >> circles[i].x >> circles[i].y >> circles[i].r;
        cout << solveCase(n, circles) << '\n';
    }
    return 0;
}
