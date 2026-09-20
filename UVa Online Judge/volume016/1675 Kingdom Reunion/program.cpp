#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

struct Point {
    int x, y;
    Point(int px = 0, int py = 0) : x(px), y(py) {}

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point &p) const {
        return !(*this == p);
    }

    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    Point operator-() const {
        return Point(-x, -y);
    }
};

typedef pair<Point, Point> Edge;
typedef tuple<int, int, ll> LineKey;
typedef map<LineKey, vector<pair<Point, int>>> Buckets;

ll cross(const Point &a, const Point &b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

ll dot(const Point &a, const Point &b) {
    return 1LL * a.x * b.x + 1LL * a.y * b.y;
}

int sign(ll x) {
    return (x > 0) - (x < 0);
}

int gcdInt(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ll areaTwo(const vector<Point> &poly) {
    int n = poly.size();
    ll area = 0;
    for (int i = 0; i < n; ++i) area += cross(poly[i], poly[(i + 1) % n]);
    return area;
}

bool readPoly(vector<Point> &poly) {
    int n;
    if (!(cin >> n)) return false;
    poly.resize(n);
    for (int i = 0; i < n; ++i) cin >> poly[i].x >> poly[i].y;
    if (areaTwo(poly) < 0) reverse(poly.begin(), poly.end());
    return true;
}

vector<Edge> getEdges(const vector<Point> &poly) {
    int n = poly.size();
    vector<Edge> edges;
    edges.reserve(n);
    for (int i = 0; i < n; ++i) edges.emplace_back(poly[i], poly[(i + 1) % n]);
    return edges;
}

struct SweepSeg {
    Point a, b;
    SweepSeg(const Point &pa, const Point &pb) : a(pa), b(pb) {}

    ld getY(ld x) const {
        if (a.x == b.x) return ((ld)a.y + b.y) / 2;
        return a.y + (x - a.x) * ((ld)b.y - a.y) / ((ld)b.x - a.x);
    }

    bool operator<(const SweepSeg &s) const {
        int leftX = max(min(a.x, b.x), min(s.a.x, s.b.x));
        int rightX = min(max(a.x, b.x), max(s.a.x, s.b.x));
        ld midX = ((ld)leftX + rightX) / 2;
        ld firstY = getY(midX), secondY = s.getY(midX);
        if (firstY != secondY) return firstY < secondY;
        Point firstHi = max(a, b), secondHi = max(s.a, s.b);
        if (firstHi != secondHi) return firstHi < secondHi;
        return min(a, b) < min(s.a, s.b);
    }
};

bool badIntersect(const SweepSeg &u, const SweepSeg &v, bool strict) {
    Point a = u.a, b = u.b, c = v.a, d = v.b;
    int r1 = sign(cross(b - a, c - a)), r2 = sign(cross(b - a, d - a));
    int r3 = sign(cross(d - c, a - c)), r4 = sign(cross(d - c, b - c));
    if (r1 == 0 && r2 == 0 && r3 == 0) {
        if (strict && dot(b - a, d - c) < 0) return false;
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return a < d && c < b;
    }
    if (a == c || a == d || b == c || b == d) return false;
    if (!strict) return r1 * r2 <= 0 && r3 * r4 <= 0;
    if (r1 * r2 < 0) return r3 * r4 < 0 || (r3 * r4 == 0 && r3 + r4 > 0);
    if (r3 * r4 < 0) return r1 * r2 < 0 || (r1 * r2 == 0 && r1 + r2 > 0);
    return false;
}

bool hasIntersection(const vector<Edge> &edges, bool strict) {
    int n = edges.size();
    vector<pair<Point, int>> events;
    vector<bool> entered(n, false), skipErase(n, false);
    set<SweepSeg> active;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        events.emplace_back(min(edges[i].first, edges[i].second), i);
        events.emplace_back(max(edges[i].first, edges[i].second), i);
    }
    sort(events.begin(), events.end());
    for (const auto &event : events) {
        int id = event.second;
        SweepSeg cur(edges[id].first, edges[id].second);
        if (entered[id]) {
            if (skipErase[id]) continue;
            auto it = active.find(cur);
            if (it == active.end()) continue;
            auto nextIt = active.erase(it);
            if (nextIt != active.begin() && nextIt != active.end()) {
                auto prevIt = prev(nextIt);
                if (badIntersect(*prevIt, *nextIt, strict)) return true;
            }
        } else {
            entered[id] = true;
            auto result = active.insert(cur);
            auto it = result.first;
            if (!result.second) {
                if (badIntersect(*it, cur, strict)) return true;
                skipErase[id] = true;
                continue;
            }
            if (it != active.begin()) {
                auto prevIt = prev(it);
                if (badIntersect(*prevIt, *it, strict)) return true;
            }
            auto nextIt = next(it);
            if (nextIt != active.end() && badIntersect(*it, *nextIt, strict)) return true;
        }
    }
    return false;
}

bool isPolygon(const vector<Point> &poly) {
    if (poly.size() < 3 || areaTwo(poly) == 0) return false;
    return !hasIntersection(getEdges(poly), false);
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    return cross(b - a, p - a) == 0 && dot(p - a, p - b) <= 0;
}

bool isInside(const Point &p, const vector<Point> &poly) {
    int n = poly.size(), winding = 0;
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSegment(a, b, p)) return false;
        ll side = cross(b - a, p - a);
        if (a.y <= p.y && b.y > p.y && side > 0) ++winding;
        if (a.y > p.y && b.y <= p.y && side < 0) --winding;
    }
    return winding != 0;
}

bool insideAngle(const Point &a, const Point &b, const Point &v) {
    if (cross(a, b) < 0) return insideAngle(a, -a, v) || insideAngle(-b, b, v);
    return cross(a, v) > 0 && cross(v, b) > 0;
}

bool sharedVertexIntersects(const vector<Point> &a, const vector<Point> &b) {
    int n = a.size(), m = b.size();
    map<Point, int> pos;
    for (int i = 0; i < n; ++i) pos[a[i]] = i;
    for (int j = 0; j < m; ++j) {
        auto it = pos.find(b[j]);
        if (it == pos.end()) continue;
        int i = it->second;
        Point aPrev = a[(i + n - 1) % n] - a[i], aNext = a[(i + 1) % n] - a[i];
        Point bPrev = b[(j + m - 1) % m] - b[j], bNext = b[(j + 1) % m] - b[j];
        if (insideAngle(aNext, aPrev, bPrev)) return true;
        if (insideAngle(aNext, aPrev, bNext)) return true;
        if (insideAngle(bNext, bPrev, aPrev)) return true;
        if (insideAngle(bNext, bPrev, aNext)) return true;
    }
    return false;
}

bool polygonsIntersect(const vector<Point> &a, const vector<Point> &b) {
    if (isInside(a[0], b) || isInside(b[0], a)) return true;
    if (sharedVertexIntersects(a, b)) return true;
    vector<Edge> edges = getEdges(a), other = getEdges(b);
    edges.insert(edges.end(), other.begin(), other.end());
    return hasIntersection(edges, true);
}

LineKey getLineKey(const Point &u, const Point &v) {
    int a = u.y - v.y, b = v.x - u.x;
    int g = gcdInt(a, b);
    a /= g;
    b /= g;
    if (a < 0 || (a == 0 && b < 0)) {
        a = -a;
        b = -b;
    }
    ll c = 1LL * a * u.x + 1LL * b * u.y;
    return make_tuple(a, b, c);
}

void addEdges(const vector<Point> &poly, Buckets &buckets) {
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i + 1) % n];
        LineKey key = getLineKey(a, b);
        buckets[key].emplace_back(min(a, b), 1);
        buckets[key].emplace_back(max(a, b), -1);
    }
}

vector<Edge> getBoundary(const vector<Point> &a, const vector<Point> &b) {
    Buckets buckets;
    vector<Edge> result;
    addEdges(a, buckets);
    addEdges(b, buckets);
    for (auto &entry : buckets) {
        auto &events = entry.second;
        sort(events.begin(), events.end());
        int count = 0, i = 0, size = events.size();
        size_t lineStart = result.size();
        Point last;
        bool hasLast = false;
        while (i < size) {
            Point cur = events[i].first;
            if (hasLast && count == 1 && last != cur) {
                if (result.size() > lineStart && result.back().second == last) result.back().second = cur;
                else result.emplace_back(last, cur);
            }
            int delta = 0;
            while (i < size && events[i].first == cur) {
                delta += events[i].second;
                ++i;
            }
            count += delta;
            last = cur;
            hasLast = true;
        }
    }
    sort(result.begin(), result.end());
    return result;
}

bool unionEquals(const vector<Point> &a, const vector<Point> &b, const vector<Point> &c) {
    vector<Point> empty;
    return getBoundary(a, b) == getBoundary(c, empty);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Point> a, b, c;
    while (readPoly(a)) {
        if (!readPoly(b) || !readPoly(c)) break;
        if (!isPolygon(a)) cout << "Aastria is not a polygon\n";
        else if (!isPolygon(b)) cout << "Abstria is not a polygon\n";
        else if (!isPolygon(c)) cout << "Aabstria is not a polygon\n";
        else if (polygonsIntersect(a, b)) cout << "Aastria and Abstria intersect\n";
        else if (!unionEquals(a, b, c)) cout << "The union of Aastria and Abstria is not equal to Aabstria\n";
        else cout << "OK\n";
    }
    return 0;
}
