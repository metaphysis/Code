// The Amazing Triangle Counting Machine
// UVa ID: 11618
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

using Point = pair<long long, long long>;

long long parseCoordinate(const string &value) {
    bool isNegative = false;
    int index = 0;
    if (value[index] == '-') {
        isNegative = true;
        ++index;
    }
    long long integerPart = 0;
    while (index < static_cast<int>(value.size()) && value[index] != '.') {
        integerPart = integerPart * 10 + value[index] - '0';
        ++index;
    }
    long long result = integerPart * 10;
    if (index < static_cast<int>(value.size()) && value[index] == '.' && index + 1 < static_cast<int>(value.size()))
        result += value[index + 1] - '0';
    return isNegative ? -result : result;
}

bool isNonCollinear(const Point &firstPoint, const Point &secondPoint, const Point &thirdPoint) {
    long long firstVectorX = secondPoint.first - firstPoint.first;
    long long firstVectorY = secondPoint.second - firstPoint.second;
    long long secondVectorX = thirdPoint.first - firstPoint.first;
    long long secondVectorY = thirdPoint.second - firstPoint.second;
    long long crossProduct = firstVectorX * secondVectorY - firstVectorY * secondVectorX;
    return crossProduct != 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--) {
        int segmentCount;
        cin >> segmentCount;
        map<Point, int> pointId;
        vector<Point> points;
        vector<unordered_set<int>> adjacency;
        auto getPointId = [&](const Point &point) {
            auto iterator = pointId.find(point);
            if (iterator != pointId.end())
                return iterator->second;
            int id = static_cast<int>(points.size());
            pointId[point] = id;
            points.push_back(point);
            adjacency.emplace_back();
            return id;
        };
        for (int segmentIndex = 0; segmentIndex < segmentCount; ++segmentIndex) {
            string firstX;
            string firstY;
            string secondX;
            string secondY;
            cin >> firstX >> firstY >> secondX >> secondY;
            Point firstPoint = {parseCoordinate(firstX), parseCoordinate(firstY)};
            Point secondPoint = {parseCoordinate(secondX), parseCoordinate(secondY)};
            int firstId = getPointId(firstPoint);
            int secondId = getPointId(secondPoint);
            if (firstId != secondId) {
                adjacency[firstId].insert(secondId);
                adjacency[secondId].insert(firstId);
            }
        }
        long long triangleCount = 0;
        int pointCount = static_cast<int>(points.size());
        for (int firstId = 0; firstId < pointCount; ++firstId) {
            for (int secondId : adjacency[firstId]) {
                if (secondId <= firstId)
                    continue;
                for (int thirdId : adjacency[firstId]) {
                    if (thirdId <= secondId)
                        continue;
                    if (!adjacency[secondId].count(thirdId))
                        continue;
                    if (isNonCollinear(points[firstId], points[secondId], points[thirdId]))
                        ++triangleCount;
                }
            }
        }
        cout << triangleCount << '\n';
    }
    return 0;
}
