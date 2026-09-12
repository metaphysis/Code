// Saskatchewan
// UVa ID: 10031
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 1.470s

#include <bits/stdc++.h>
using namespace std;

using LongLong = long long;
using Point = pair<LongLong, LongLong>;
using Interval = pair<LongLong, LongLong>;

const long double Epsilon = 1e-12L;

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    if (intervals.empty())
        return intervals;
    sort(intervals.begin(), intervals.end());
    vector<Interval> result;
    result.push_back(intervals[0]);
    for (size_t i = 1; i < intervals.size(); ++i) {
        Interval& last = result.back();
        if (intervals[i].first <= last.second + 1)
            last.second = max(last.second, intervals[i].second);
        else
            result.push_back(intervals[i]);
    }
    return result;
}

LongLong solve(const vector<Point>& points) {
    int pointCount = points.size();
    LongLong maxX = 0;
    LongLong maxY = 0;
    for (const Point& point : points) {
        maxX = max(maxX, point.first);
        maxY = max(maxY, point.second);
    }

    LongLong answer = 0;

    for (LongLong row = 0; row < maxY; ++row) {
        long double scanY = row + 0.5L;
        vector<long double> intersections;
        vector<Interval> blockedIntervals;

        for (int i = 0; i < pointCount; ++i) {
            LongLong x1 = points[i].first;
            LongLong y1 = points[i].second;
            LongLong x2 = points[(i + 1) % pointCount].first;
            LongLong y2 = points[(i + 1) % pointCount].second;

            if (y1 == y2)
                continue;

            if ((y1 <= scanY && scanY < y2) || (y2 <= scanY && scanY < y1)) {
                long double x = x1 + (x2 - x1) * (scanY - y1) / (y2 - y1);
                intersections.push_back(x);
            }

            LongLong lowY = min(y1, y2);
            LongLong highY = max(y1, y2);
            if (lowY > row || row >= highY)
                continue;

            long double xAtLow = x1 + (x2 - x1) * (static_cast<long double>(row) - y1) / (y2 - y1);
            long double xAtHigh = x1 + (x2 - x1) * (static_cast<long double>(row + 1) - y1) / (y2 - y1);
            long double leftX = min(xAtLow, xAtHigh);
            long double rightX = max(xAtLow, xAtHigh);

            if (rightX - leftX <= Epsilon)
                continue;

            LongLong left = static_cast<LongLong>(floor(leftX + Epsilon));
            LongLong right = static_cast<LongLong>(ceil(rightX - Epsilon)) - 1;
            left = max<LongLong>(left, 0);
            right = min<LongLong>(right, maxX - 1);
            if (left <= right)
                blockedIntervals.push_back({left, right});
        }

        sort(intersections.begin(), intersections.end());
        vector<Interval> insideIntervals;
        for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
            long double leftX = intersections[i];
            long double rightX = intersections[i + 1];

            LongLong left = static_cast<LongLong>(floor(leftX - 0.5L + Epsilon)) + 1;
            LongLong right = static_cast<LongLong>(ceil(rightX - 0.5L - Epsilon)) - 1;
            left = max<LongLong>(left, 0);
            right = min<LongLong>(right, maxX - 1);
            if (left <= right)
                insideIntervals.push_back({left, right});
        }

        blockedIntervals = mergeIntervals(blockedIntervals);

        // 两个区间集合均有序，用双指针在线性时间内扣除边界穿过的 section。
        size_t blockedIndex = 0;
        for (const Interval& inside : insideIntervals) {
            answer += inside.second - inside.first + 1;

            while (blockedIndex < blockedIntervals.size() && blockedIntervals[blockedIndex].second < inside.first)
                ++blockedIndex;

            size_t currentIndex = blockedIndex;
            while (currentIndex < blockedIntervals.size() && blockedIntervals[currentIndex].first <= inside.second) {
                LongLong left = max(inside.first, blockedIntervals[currentIndex].first);
                LongLong right = min(inside.second, blockedIntervals[currentIndex].second);
                if (left <= right)
                    answer -= right - left + 1;

                if (blockedIntervals[currentIndex].second > inside.second)
                    break;
                ++currentIndex;
            }

            blockedIndex = currentIndex;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseCount;
    cin >> caseCount;
    string line;
    getline(cin, line);

    for (int caseIndex = 0; caseIndex < caseCount; ++caseIndex) {
        vector<Point> points;
        while (getline(cin, line)) {
            if (line.empty()) {
                if (!points.empty())
                    break;
                continue;
            }

            stringstream input(line);
            LongLong x;
            LongLong y;
            input >> x >> y;
            points.push_back({x, y});
        }

        cout << solve(points) << '\n';
        if (caseIndex + 1 < caseCount)
            cout << '\n';
    }

    return 0;
}
