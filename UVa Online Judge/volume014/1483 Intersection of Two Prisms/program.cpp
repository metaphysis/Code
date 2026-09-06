#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

struct Polygon {
    Point point[105];
    int count;
};

long double lineValue(const Polygon &polygon, int edge, long double x) {
    int nextEdge = (edge + 1) % polygon.count;
    Point first = polygon.point[edge], second = polygon.point[nextEdge];
    return first.y + (second.y - first.y) * (x - first.x) / (second.x - first.x);
}

bool getEdgePair(const Polygon &polygon, long double x, int &lowEdge, int &highEdge) {
    int edgeCount = polygon.count;
    long double lowValue = 1e100L, highValue = -1e100L;
    lowEdge = -1, highEdge = -1;
    for (int edge = 0; edge < edgeCount; edge++) {
        int nextEdge = (edge + 1) % edgeCount;
        long double firstX = polygon.point[edge].x, secondX = polygon.point[nextEdge].x;
        if (firstX == secondX) continue;
        if (!((firstX < x && x < secondX) || (secondX < x && x < firstX))) continue;
        long double value = lineValue(polygon, edge, x);
        if (value < lowValue) {
            lowValue = value;
            lowEdge = edge;
        }
        if (value > highValue) {
            highValue = value;
            highEdge = edge;
        }
    }
    return lowEdge != -1 && highEdge != -1;
}

long double getLength(const Polygon &polygon, int lowEdge, int highEdge, long double x) {
    return lineValue(polygon, highEdge, x) - lineValue(polygon, lowEdge, x);
}

long double calcVolume(const Polygon &first, const Polygon &second, vector<long double> values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end(), [](long double first, long double second) {
        return fabsl(first - second) < 1e-12L;
    }), values.end());
    long double volume = 0;
    int valueCount = values.size();
    for (int index = 0; index + 1 < valueCount; index++) {
        long double left = values[index], right = values[index + 1], middle = (left + right) / 2;
        int firstLow, firstHigh, secondLow, secondHigh;
        if (!getEdgePair(first, middle, firstLow, firstHigh)) continue;
        if (!getEdgePair(second, middle, secondLow, secondHigh)) continue;
        long double firstLeft = getLength(first, firstLow, firstHigh, left);
        long double firstRight = getLength(first, firstLow, firstHigh, right);
        long double secondLeft = getLength(second, secondLow, secondHigh, left);
        long double secondRight = getLength(second, secondLow, secondHigh, right);
        long double width = right - left;
        long double firstDelta = firstRight - firstLeft, secondDelta = secondRight - secondLeft;
        volume += width * (firstLeft * secondLeft + (firstLeft * secondDelta + secondLeft * firstDelta) / 2 + firstDelta * secondDelta / 3);
    }
    return volume;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        Polygon first, second;
        first.count = m;
        second.count = n;
        vector<long double> values;
        for (int index = 0; index < m; index++) {
            cin >> first.point[index].x >> first.point[index].y;
            values.push_back(first.point[index].x);
        }
        for (int index = 0; index < n; index++) {
            cin >> second.point[index].x >> second.point[index].y;
            values.push_back(second.point[index].x);
        }
        long double answer = calcVolume(first, second, values);
        cout << fixed << setprecision(10) << answer << '\n';
    }
    return 0;
}
