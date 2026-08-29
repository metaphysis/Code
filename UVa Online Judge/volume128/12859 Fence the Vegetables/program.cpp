#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    int x, y;
};

vector<Point> points;

bool cmpPoint(const Point &a, const Point &b, bool top) {
    if (a.x != b.x) return a.x < b.x;
    return top ? a.y < b.y : a.y > b.y;
}

bool removable(const Point &a, const Point &b, const Point &c, bool top) {
    return top ? a.y >= b.y && c.y >= b.y : a.y <= b.y && c.y <= b.y;
}

ll buildBorder(bool top) {
    vector<Point> stackList, border;
    sort(points.begin(), points.end(), [top](const Point &a, const Point &b) { return cmpPoint(a, b, top); });
    for (int i = 0; i < (int)points.size(); ++i) {
        while (i + 1 < (int)points.size() && points[i + 1].x == points[i].x) ++i;
        while (stackList.size() >= 2 && removable(stackList[stackList.size() - 2], stackList.back(), points[i], top)) stackList.pop_back();
        stackList.push_back(points[i]);
    }
    int d = top ? 1 : -1;
    border.push_back({stackList[0].x - 1, stackList[0].y + d});
    int turn = -1;
    for (int i = 1; i < (int)stackList.size(); ++i) {
        if ((top && stackList[i].y < stackList[i - 1].y) || (!top && stackList[i].y > stackList[i - 1].y)) {
            turn = i;
            break;
        }
        border.push_back({stackList[i].x - 1, stackList[i - 1].y + d});
        border.push_back({stackList[i].x - 1, stackList[i].y + d});
    }
    if (turn != -1)
        for (int i = turn; i < (int)stackList.size(); ++i) {
            border.push_back({stackList[i - 1].x + 1, stackList[i - 1].y + d});
            border.push_back({stackList[i - 1].x + 1, stackList[i].y + d});
        }
    border.push_back({stackList.back().x + 1, stackList.back().y + d});
    ll area = 0;
    for (int i = 0; i < (int)border.size(); i += 2) area += (ll)border[i].y * (border[i + 1].x - border[i].x);
    if (top) {
        border[0].x = stackList[0].x;
        border.back().x = stackList.back().x;
        points.insert(points.end(), border.begin(), border.end());
    }
    return area;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        points.resize(n);
        int minX, maxX, minY, maxY;
        for (int i = 0; i < n; ++i) scanf("%d%d", &points[i].x, &points[i].y);
        if (n == 1) {
            puts("8 4");
            continue;
        }
        minX = maxX = points[0].x;
        minY = maxY = points[0].y;
        for (const Point &point : points) {
            minX = min(minX, point.x);
            maxX = max(maxX, point.x);
            minY = min(minY, point.y);
            maxY = max(maxY, point.y);
        }
        ll perimeter = 2LL * (maxX - minX + maxY - minY) + 8;
        ll area = buildBorder(true) - buildBorder(false);
        printf("%lld %lld\n", perimeter, area);
    }
    return 0;
}
