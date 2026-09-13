#include <bits/stdc++.h>
using namespace std;

const int maxN = 3005;

struct Point {
    int x, y, id;
    bool operator < (const Point &other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

Point pointList[maxN], hullList[maxN * 2];
bool removed[maxN];

long long cross(const Point &a, const Point &b, const Point &c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

int buildHull(int pointCount) {
    int i, hullCount, lowerCount;
    sort(pointList, pointList + pointCount);
    hullCount = 0;
    for (i = 0; i < pointCount; i++) {
        while (hullCount >= 2 && cross(hullList[hullCount - 2], hullList[hullCount - 1], pointList[i]) < 0) hullCount--;
        hullList[hullCount++] = pointList[i];
    }
    lowerCount = hullCount;
    for (i = pointCount - 2; i >= 0; i--) {
        while (hullCount > lowerCount && cross(hullList[hullCount - 2], hullList[hullCount - 1], pointList[i]) < 0) hullCount--;
        hullList[hullCount++] = pointList[i];
    }
    if (hullCount > 1) hullCount--;
    return hullCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int pointCount, age, hullCount, remainCount, i;
    while (cin >> pointCount) {
        for (i = 0; i < pointCount; i++) {
            cin >> pointList[i].x >> pointList[i].y;
            pointList[i].id = i;
        }
        age = 0;
        while (pointCount > 0) {
            hullCount = buildHull(pointCount);
            memset(removed, false, sizeof(removed));
            for (i = 0; i < hullCount; i++) removed[hullList[i].id] = true;
            remainCount = 0;
            for (i = 0; i < pointCount; i++)
                if (!removed[pointList[i].id]) pointList[remainCount++] = pointList[i];
            pointCount = remainCount;
            age++;
        }
        cout << age << '\n';
    }
    return 0;
}
