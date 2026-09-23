#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Event {
    int x, yLow, yHigh, delta;
};

struct SegTree {
    vector<int> minVal, lazyVal;
    void init(int size) {
        minVal.assign(size * 4 + 4, 0);
        lazyVal.assign(size * 4 + 4, 0);
    }

    void add(int node, int left, int right, int queryLeft, int queryRight, int delta) {
        if (queryLeft <= left && right <= queryRight) {
            minVal[node] += delta;
            lazyVal[node] += delta;
            return;
        }
        int mid = (left + right) / 2;
        if (queryLeft <= mid) add(node * 2, left, mid, queryLeft, queryRight, delta);
        if (queryRight > mid) add(node * 2 + 1, mid + 1, right, queryLeft, queryRight, delta);
        minVal[node] = min(minVal[node * 2], minVal[node * 2 + 1]) + lazyVal[node];
    }
};

bool hasHigher(const vector<Point> &points, int height) {
    int n = points.size();
    vector<Event> events;
    vector<int> yVals;
    events.reserve(n * 3);
    yVals.reserve(n * 4);
    for (int i = 0; i < n; ++i) {
        const Point &a = points[i], &b = points[(i + 1) % n];
        int xLow = min(a.x, b.x) - height, xHigh = max(a.x, b.x) + height;
        int yLow = min(a.y, b.y) - height, yHigh = max(a.y, b.y) + height;
        events.push_back({xLow, yLow, yHigh, 1});
        events.push_back({xHigh, yLow, yHigh, -1});
        yVals.push_back(yLow);
        yVals.push_back(yHigh);
        if (a.x == b.x) {
            int edgeLow = min(a.y, b.y), edgeHigh = max(a.y, b.y);
            int delta = a.y < b.y ? 1 : -1;
            events.push_back({a.x, edgeLow, edgeHigh, delta});
            yVals.push_back(edgeLow);
            yVals.push_back(edgeHigh);
        }
    }
    sort(yVals.begin(), yVals.end());
    yVals.erase(unique(yVals.begin(), yVals.end()), yVals.end());
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) { return a.x < b.x; });
    int segCount = yVals.size() - 1, eventCount = events.size();
    SegTree segTree;
    segTree.init(segCount);
    for (int i = 0; i < eventCount; ) {
        int j = i;
        while (j < eventCount && events[j].x == events[i].x) {
            int left = lower_bound(yVals.begin(), yVals.end(), events[j].yLow) - yVals.begin();
            int right = lower_bound(yVals.begin(), yVals.end(), events[j].yHigh) - yVals.begin() - 1;
            if (left <= right) segTree.add(1, 0, segCount - 1, left, right, events[j].delta);
            ++j;
        }
        if (j < eventCount && segTree.minVal[1] < 0) return true;
        i = j;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(1);
    while (testCount--) {
        int n, minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
        cin >> n;
        vector<Point> points(n);
        for (Point &point : points) {
            cin >> point.x >> point.y;
            point.x *= 2;
            point.y *= 2;
            minX = min(minX, point.x);
            maxX = max(maxX, point.x);
            minY = min(minY, point.y);
            maxY = max(maxY, point.y);
        }
        int low = 0, high = min(maxX - minX, maxY - minY) / 2;
        while (low < high) {
            int mid = (low + high) / 2;
            if (hasHigher(points, mid)) low = mid + 1;
            else high = mid;
        }
        cout << low / 2.0 << '\n';
    }
    return 0;
}
