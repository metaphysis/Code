// The Picnic
// UVa ID: 1634
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.490s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long distanceSquare(const Point &a, const Point &b) {
    long long deltaX = a.x - b.x;
    long long deltaY = a.y - b.y;
    return deltaX * deltaX + deltaY * deltaY;
}

bool isEmptyTriangle(int originIndex, int firstIndex, int secondIndex, const vector<Point> &points) {
    const Point &origin = points[originIndex];
    const Point &first = points[firstIndex];
    const Point &second = points[secondIndex];
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        if (i == originIndex || i == firstIndex || i == secondIndex)
            continue;
        long long firstCross = cross(origin, first, points[i]);
        long long secondCross = cross(first, second, points[i]);
        long long thirdCross = cross(second, origin, points[i]);
        if (firstCross > 0 && secondCross > 0 && thirdCross > 0)
            return false;
    }
    return true;
}

bool hasPointOnSegment(int firstIndex, int secondIndex, const vector<Point> &points) {
    const Point &first = points[firstIndex];
    const Point &second = points[secondIndex];
    long long segmentLength = distanceSquare(first, second);
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        if (i == firstIndex || i == secondIndex)
            continue;
        if (cross(first, second, points[i]) != 0)
            continue;
        long long firstDeltaX = points[i].x - first.x;
        long long firstDeltaY = points[i].y - first.y;
        long long secondDeltaX = points[i].x - second.x;
        long long secondDeltaY = points[i].y - second.y;
        long long firstDot = firstDeltaX * (second.x - first.x) + firstDeltaY * (second.y - first.y);
        long long secondDot = secondDeltaX * (first.x - second.x) + secondDeltaY * (first.y - second.y);
        if (firstDot > 0 && secondDot > 0 && firstDot < segmentLength)
            return true;
    }
    return false;
}

double solveScenario(const vector<Point> &points) {
    int pointCount = static_cast<int>(points.size());
    long long answer = 0;
    for (int originIndex = 0; originIndex < pointCount; ++originIndex) {
        vector<int> order;
        for (int i = 0; i < pointCount; ++i) {
            if (i == originIndex)
                continue;
            if (points[i].y > points[originIndex].y || (points[i].y == points[originIndex].y && points[i].x > points[originIndex].x))
                order.push_back(i);
        }
        sort(order.begin(), order.end(), [&](int firstIndex, int secondIndex) {
            long long directionCross = cross(points[originIndex], points[firstIndex], points[secondIndex]);
            if (directionCross != 0)
                return directionCross > 0;
            return distanceSquare(points[originIndex], points[firstIndex]) < distanceSquare(points[originIndex], points[secondIndex]);
        });
        int candidateCount = static_cast<int>(order.size());
        vector<vector<long long>> triangleArea(candidateCount, vector<long long>(candidateCount, -1));
        vector<vector<bool>> triangleEmpty(candidateCount, vector<bool>(candidateCount, false));
        vector<bool> radialEmpty(candidateCount, true);
        for (int i = 0; i < candidateCount; ++i) {
            radialEmpty[i] = !hasPointOnSegment(originIndex, order[i], points);
            for (int j = i + 1; j < candidateCount; ++j) {
                if (cross(points[originIndex], points[order[i]], points[order[j]]) <= 0)
                    continue;
                if (!isEmptyTriangle(originIndex, order[i], order[j], points))
                    continue;
                triangleEmpty[i][j] = true;
                triangleArea[i][j] = cross(points[originIndex], points[order[i]], points[order[j]]);
                answer = max(answer, triangleArea[i][j]);
            }
        }
        vector<vector<long long>> best(candidateCount, vector<long long>(candidateCount, -1));
        for (int i = 0; i < candidateCount; ++i) {
            for (int j = i + 1; j < candidateCount; ++j) {
                if (!triangleEmpty[i][j])
                    continue;
                for (int k = 0; k < i; ++k) {
                    if (!radialEmpty[i])
                        continue;
                    if (cross(points[order[k]], points[order[i]], points[order[j]]) <= 0)
                        continue;
                    if (triangleArea[k][i] != -1)
                        best[i][j] = max(best[i][j], triangleArea[k][i] + triangleArea[i][j]);
                    if (best[k][i] != -1)
                        best[i][j] = max(best[i][j], best[k][i] + triangleArea[i][j]);
                }
                answer = max(answer, best[i][j]);
            }
        }
    }
    return answer / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int obstacleCount;
        cin >> obstacleCount;
        vector<Point> points(obstacleCount);
        for (int i = 0; i < obstacleCount; ++i)
            cin >> points[i].x >> points[i].y;
        cout << fixed << setprecision(1) << solveScenario(points) << '\n';
    }
    return 0;
}
