// Peaceful Sharing
// UVa ID: 10797
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x;
    long double y;
};

struct MedianPoint {
    long double value;
    int id;
};

MedianPoint getMedian(const vector<Point>& points, long double slope) {
    vector<pair<long double, int>> values;
    values.reserve(points.size());
    for (int i = 0; i < static_cast<int>(points.size()); i++) {
        values.push_back({points[i].y - slope * points[i].x, i});
    }
    int middle = static_cast<int>(values.size()) / 2;
    nth_element(values.begin(), values.begin() + middle, values.end());
    return {values[middle].first, values[middle].second};
}

long double getDifference(const vector<Point>& goldPoints, const vector<Point>& coalPoints, long double slope) {
    MedianPoint goldMedian = getMedian(goldPoints, slope);
    MedianPoint coalMedian = getMedian(coalPoints, slope);
    return goldMedian.value - coalMedian.value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int caseNumber = 1;
    while (cin >> n && n != 0) {
        vector<Point> goldPoints;
        vector<Point> coalPoints;
        int goldCount = 0;
        int coalCount = 0;
        for (int i = 0; i < n; i++) {
            long double x;
            long double y;
            cin >> x >> y;
            if (x < 0) {
                goldPoints.push_back({x, y});
                goldCount++;
            } else {
                coalPoints.push_back({x, y});
                coalCount++;
            }
        }
        long double left = -1.0e9L;
        long double right = 1.0e9L;
        for (int iteration = 0; iteration < 100; iteration++) {
            long double middle = (left + right) / 2.0L;
            if (getDifference(goldPoints, coalPoints, middle) < 0) left = middle;
            else right = middle;
        }
        long double slope = (left + right) / 2.0L;
        MedianPoint goldMedian = getMedian(goldPoints, slope);
        MedianPoint coalMedian = getMedian(coalPoints, slope);
        cout << "Case " << caseNumber++ << ": ";
        cout << goldMedian.id << ' ' << coalMedian.id << '\n';
    }
    return 0;
}
