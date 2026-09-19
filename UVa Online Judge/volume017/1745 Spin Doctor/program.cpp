#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point operator-(const Point &p) const {
        return {x - p.x, y - p.y};
    }
};

struct Event {
    Point dir;
    int delta;
};

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long long dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

bool pointLess(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool pointEqual(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

vector<Point> buildHull(vector<Point> points) {
    sort(points.begin(), points.end(), pointLess);
    points.erase(unique(points.begin(), points.end(), pointEqual), points.end());
    int size = (int)points.size(), len = 0, limit;
    if (size == 1) return points;
    vector<Point> hull(2 * size);
    for (int i = 0; i < size; ++i) {
        while (len >= 2 && cross(hull[len - 1] - hull[len - 2], points[i] - hull[len - 2]) <= 0) --len;
        hull[len++] = points[i];
    }
    limit = len + 1;
    for (int i = size - 2; i >= 0; --i) {
        while (len >= limit && cross(hull[len - 1] - hull[len - 2], points[i] - hull[len - 2]) <= 0) --len;
        hull[len++] = points[i];
    }
    hull.resize(len - 1);
    return hull;
}

bool isVisible(const vector<Point> &hull, Point q, int id) {
    int size = (int)hull.size();
    return cross(hull[(id + 1) % size] - hull[id], q - hull[id]) < 0;
}

int findVisible(const vector<Point> &hull, Point q) {
    int size = (int)hull.size(), left = 1, right = size - 1, mid;
    if (cross(hull[1] - hull[0], q - hull[0]) < 0) return 0;
    if (cross(hull[size - 1] - hull[0], q - hull[0]) > 0) return size - 1;
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (cross(hull[mid] - hull[0], q - hull[0]) >= 0) left = mid;
        else right = mid;
    }
    if (isVisible(hull, q, left)) return left;
    return -1;
}

int angleHalf(Point v, Point base) {
    long long turn = cross(base, v);
    if (turn > 0 || (turn == 0 && dot(base, v) > 0)) return 0;
    return 1;
}

bool angleLess(Point a, Point b, Point base) {
    int halfA = angleHalf(a, base), halfB = angleHalf(b, base);
    if (halfA != halfB) return halfA < halfB;
    return cross(a, b) > 0;
}

Point centerRay(Point p, Point center) {
    return {3 * p.x - center.x, 3 * p.y - center.y};
}

bool findTangents(const vector<Point> &hull, Point q, Point center, Point &u, Point &v) {
    int size = (int)hull.size(), vis = findVisible(hull, q);
    int left = 0, right = size, mid, hidden, dist, first, last;
    if (vis == -1) return false;
    Point base = centerRay(hull[0], center), target = {center.x - 3 * q.x, center.y - 3 * q.y};
    // 二分寻找穿过内部重心后，远离查询点的射线所碰到的边
    while (left < right) {
        mid = (left + right) / 2;
        if (angleLess(centerRay(hull[mid], center), target, base)) left = mid + 1;
        else right = mid;
    }
    hidden = (left + size - 1) % size;
    // 沿逆时针方向寻找最后一条可见边
    dist = (hidden - vis + size) % size;
    left = 0;
    right = dist;
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (isVisible(hull, q, (vis + mid) % size)) left = mid;
        else right = mid;
    }
    last = (vis + left) % size;
    // 沿顺时针方向寻找第一条可见边
    dist = (vis - hidden + size) % size;
    left = 0;
    right = dist;
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (isVisible(hull, q, (vis - mid + size) % size)) left = mid;
        else right = mid;
    }
    first = (vis - left + size) % size;
    u = hull[first] - q;
    v = hull[(last + 1) % size] - q;
    return true;
}

Point normalizeDir(Point dir) {
    if (dir.y < 0 || (dir.y == 0 && dir.x < 0)) {
        dir.x = -dir.x;
        dir.y = -dir.y;
    }
    return dir;
}

bool eventLess(const Event &a, const Event &b) {
    return cross(a.dir, b.dir) > 0;
}

int solve(const vector<Point> &ones, const vector<Point> &zeros) {
    int oneCount = (int)ones.size(), total = oneCount + (int)zeros.size();
    if (oneCount == 1) return 1;
    vector<Point> hull = buildHull(ones);
    int size = (int)hull.size(), outside = 0, best, answer = oneCount;
    if (size == 1) {
        for (const Point &q : zeros) if (pointEqual(q, hull[0])) ++answer;
        return answer;
    }
    Point center = {0, 0};
    if (size >= 3) {
        center.x = hull[0].x + hull[1].x + hull[size - 1].x;
        center.y = hull[0].y + hull[1].y + hull[size - 1].y;
    }
    vector<Event> events;
    events.reserve(2 * zeros.size());
    for (const Point &q : zeros) {
        Point u, v, startDir, endDir;
        if (size == 2) {
            u = hull[0] - q;
            v = hull[1] - q;
            if (cross(u, v) == 0) {
                if (dot(u, v) > 0) ++outside;
                continue;
            }
            if (cross(u, v) > 0) swap(u, v);
        } else {
            if (!findTangents(hull, q, center, u, v)) continue;
        }
        startDir = normalizeDir({u.y, -u.x});
        endDir = normalizeDir({-v.y, v.x});
        events.push_back({startDir, 1});
        events.push_back({endDir, -1});
        if (cross(startDir, endDir) < 0) ++outside;
    }
    sort(events.begin(), events.end(), eventLess);
    best = outside;
    for (int i = 0, j, delta; i < (int)events.size(); i = j) {
        j = i;
        delta = 0;
        while (j < (int)events.size() && cross(events[i].dir, events[j].dir) == 0) {
            delta += events[j].delta;
            ++j;
        }
        outside += delta;
        best = max(best, outside);
    }
    return total - best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> ones, zeros;
        for (int i = 0, c; i < n; ++i) {
            Point p;
            cin >> p.x >> p.y >> c;
            if (c == 1) ones.push_back(p);
            else zeros.push_back(p);
        }
        cout << solve(ones, zeros) << '\n';
    }
    return 0;
}
