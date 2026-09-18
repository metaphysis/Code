#include <bits/stdc++.h>
using namespace std;

struct Contour {
    int height;
    long long area;
    vector<pair<long long, long long>> points;
};

bool isInside(const Contour &contour, long long x, long long y) {
    bool inside = false;
    int n = contour.points.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        long long xi = contour.points[i].first, yi = contour.points[i].second;
        long long xj = contour.points[j].first, yj = contour.points[j].second;
        if ((yi > y) != (yj > y)) {
            long double crossX = static_cast<long double>(xj - xi) * (y - yi) / (yj - yi) + xi;
            if (x < crossX)
                inside = !inside;
        }
    }
    return inside;
}

long long getArea(const vector<pair<long long, long long>> &points) {
    long long area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += points[i].first * points[j].second - points[j].first * points[i].second;
    }
    return area >= 0 ? area : -area;
}

void solve() {
    int n;
    cin >> n;
    vector<Contour> contours(n);
    vector<int> aliceList, bobList;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> contours[i].height >> p;
        contours[i].points.resize(p);
        for (int j = 0; j < p; j++)
            cin >> contours[i].points[j].first >> contours[i].points[j].second;
        contours[i].area = getArea(contours[i].points);
        if (isInside(contours[i], 0, 0))
            aliceList.push_back(i);
        if (isInside(contours[i], 100000, 0))
            bobList.push_back(i);
    }
    sort(aliceList.begin(), aliceList.end(), [&](int x, int y) {
        return contours[x].area < contours[y].area;
    });
    sort(bobList.begin(), bobList.end(), [&](int x, int y) {
        return contours[x].area > contours[y].area;
    });
    vector<int> route;
    for (int index : aliceList) {
        if (!isInside(contours[index], 100000, 0))
            route.push_back(index);
    }
    for (int index : bobList) {
        if (!isInside(contours[index], 0, 0))
            route.push_back(index);
    }
    long long climb = 0, descend = 0;
    for (int i = 1; i < static_cast<int>(route.size()); i++) {
        long long delta = contours[route[i]].height - contours[route[i - 1]].height;
        if (delta > 0)
            climb += delta;
        else
            descend -= delta;
    }
    cout << climb << ' ' << descend << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    while (testCase--)
        solve();
    return 0;
}
