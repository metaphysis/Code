#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;

const int xCoef[8] = {1, 1, -1, -1, 0, 0, 0, 0},
          yCoef[8] = {0, 0, 0, 0, 1, 1, -1, -1},
          zCoef[8] = {0, 0, 0, 0, 1, -1, 1, -1},
          wCoef[8] = {1, -1, 1, -1, 0, 0, 0, 0},
          dirSign[8] = {1, -1, -1, 1, -1, 1, 1, -1};

struct Point {
    ll x, y;
};

struct Cut {
    ll pos;
    Point a, b;
    bool valid;
};

struct Event {
    ll pos;
    int type, id;
};

struct HashVal {
    ull x, y, revX, revY;
    int len;
};

struct HalfPoly {
    Point a, b;
    int left, right, len;
    bool hasA, hasB;
    array<int, 8> anchor;
};

struct Fenwick {
    vector<int> tree;

    Fenwick(int n) : tree(n + 1, 0) {}

    void add(int pos, int val) {
        for (++pos; pos < (int)tree.size(); pos += pos & -pos) tree[pos] += val;
    }

    int sum(int pos) const {
        int ans = 0;
        for (; pos > 0; pos -= pos & -pos) ans += tree[pos];
        return ans;
    }
};

i128 cross(Point a, Point b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

i128 turn(Point a, Point b, Point c) {
    return cross(a, b) + cross(b, c) + cross(c, a);
}

Point transformPoint(Point p, int op) {
    return {xCoef[op] * p.x + yCoef[op] * p.y,
            zCoef[op] * p.x + wCoef[op] * p.y};
}

bool lessPoint(Point a, Point b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

struct Solver {
    int n, total;
    ll perimeter, half;
    vector<Point> points;
    vector<ll> dist;
    vector<i128> area;
    vector<Cut> cuts;
    vector<ull> power, geomSum, preX, preY, revX, revY;
    vector<array<int, 8>> segTree;

    int edgeAt(ll pos) const {
        return upper_bound(dist.begin(), dist.end(), pos) - dist.begin() - 1;
    }

    Point edgeDir(int id) const {
        Point a = points[id], b = points[(id + 1) % total];
        return {(b.x > a.x) - (b.x < a.x),
                (b.y > a.y) - (b.y < a.y)};
    }

    Point pointAtDist(ll pos) const {
        int id = edgeAt(pos);
        ll offset = pos - dist[id];
        Point dir = edgeDir(id);
        return {points[id].x + dir.x * offset,
                points[id].y + dir.y * offset};
    }

    void addCandidate(ll pos) {
        int firstId = edgeAt(pos), secondId = edgeAt(pos + half);
        Point a = pointAtDist(pos), b = pointAtDist(pos + half);
        if (a.x == b.x && a.y == b.y) return;
        if (a.x != b.x && a.y != b.y) return;
        i128 partArea = area[secondId] - area[firstId]
                      - cross(points[firstId], a)
                      + cross(points[secondId], b) + cross(b, a);
        if (partArea * 2 == area[n]) cuts.push_back({pos, a, b, false});
    }

    void findCandidates() {
        ll cur = 0;
        int firstId = 0, secondId = edgeAt(half);
        while (cur < half) {
            while (dist[firstId + 1] <= cur) ++firstId;
            while (dist[secondId + 1] <= cur + half) ++secondId;
            ll next = min(half, min(dist[firstId + 1], dist[secondId + 1] - half));
            Point a = pointAtDist(cur), b = pointAtDist(cur + half);
            Point firstDir = edgeDir(firstId), secondDir = edgeDir(secondId);
            addCandidate(cur);
            for (int axis = 0; axis < 2; ++axis) {
                ll delta = axis == 0 ? b.x - a.x : b.y - a.y;
                ll slope = axis == 0 ? firstDir.x - secondDir.x : firstDir.y - secondDir.y;
                if (slope == 0 || delta % slope != 0) continue;
                ll step = delta / slope;
                if (step > 0 && step < next - cur) addCandidate(cur + step);
            }
            cur = next;
        }
        sort(cuts.begin(), cuts.end(), [](const Cut &a, const Cut &b) {
            return a.pos < b.pos;
        });
        cuts.erase(unique(cuts.begin(), cuts.end(), [](const Cut &a, const Cut &b) {
            return a.pos == b.pos;
        }), cuts.end());
    }

    void validateCuts(int axis) {
        vector<ll> coords;
        vector<Event> events;
        vector<array<ll, 3>> parallelEdges;
        for (int i = 0; i < n; ++i) coords.push_back(axis == 0 ? points[i].x : points[i].y);
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        for (int i = 0; i < n; ++i) {
            Point a = points[i], b = points[i + 1];
            ll firstU = axis == 0 ? a.x : a.y, firstV = axis == 0 ? a.y : a.x;
            ll secondU = axis == 0 ? b.x : b.y, secondV = axis == 0 ? b.y : b.x;
            if (firstU == secondU) {
                int id = lower_bound(coords.begin(), coords.end(), firstU) - coords.begin();
                ll low = min(firstV, secondV), high = max(firstV, secondV);
                events.push_back({low, 1, id});
                events.push_back({high, 0, id});
                events.push_back({high, 3, id});
            } else {
                parallelEdges.push_back({{firstV, min(firstU, secondU), max(firstU, secondU)}});
            }
        }
        for (int i = 0; i < (int)cuts.size(); ++i) {
            bool horizontal = cuts[i].a.y == cuts[i].b.y;
            if (horizontal != (axis == 0)) continue;
            ll fixed = axis == 0 ? cuts[i].a.y : cuts[i].a.x;
            events.push_back({fixed, 2, i});
        }
        sort(parallelEdges.begin(), parallelEdges.end());
        sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
            return a.pos != b.pos ? a.pos < b.pos : a.type < b.type;
        });
        Fenwick closedBit(coords.size()), parityBit(coords.size());
        for (const Event &event : events) {
            if (event.type == 0) {
                parityBit.add(event.id, -1);
            } else if (event.type == 1) {
                closedBit.add(event.id, 1);
                parityBit.add(event.id, 1);
            } else if (event.type == 3) {
                closedBit.add(event.id, -1);
            } else {
                Cut &cut = cuts[event.id];
                ll firstU = axis == 0 ? cut.a.x : cut.a.y;
                ll secondU = axis == 0 ? cut.b.x : cut.b.y;
                ll low = min(firstU, secondU), high = max(firstU, secondU);
                int left = upper_bound(coords.begin(), coords.end(), low) - coords.begin();
                int right = lower_bound(coords.begin(), coords.end(), high) - coords.begin();
                if (closedBit.sum(right) - closedBit.sum(left) != 0) continue;
                array<ll, 3> key = {{event.pos, high, LLONG_MIN}};
                auto it = lower_bound(parallelEdges.begin(), parallelEdges.end(), key);
                if (it != parallelEdges.begin()) {
                    --it;
                    if ((*it)[0] == event.pos && (*it)[2] > low) continue;
                }
                if (parityBit.sum(left) & 1) cut.valid = true;
            }
        }
    }

    int betterIndex(int first, int second, int op) const {
        if (first == -1) return second;
        if (second == -1) return first;
        Point a = transformPoint(points[first], op), b = transformPoint(points[second], op);
        return lessPoint(a, b) ? first : second;
    }

    array<int, 8> mergeMin(const array<int, 8> &a, const array<int, 8> &b) const {
        array<int, 8> result;
        for (int op = 0; op < 8; ++op) result[op] = betterIndex(a[op], b[op], op);
        return result;
    }

    array<int, 8> queryMin(int left, int right) const {
        array<int, 8> result;
        result.fill(-1);
        for (left += total, right += total; left < right; left /= 2, right /= 2) {
            if (left & 1) result = mergeMin(result, segTree[left++]);
            if (right & 1) result = mergeMin(result, segTree[--right]);
        }
        return result;
    }

    void prepareCompare() {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        ull base = rng() | 257ULL;
        power.resize(total + 1);
        geomSum.resize(total + 1);
        preX.resize(total + 1);
        preY.resize(total + 1);
        revX.resize(total + 1);
        revY.resize(total + 1);
        power[0] = 1;
        for (int i = 0; i < total; ++i) {
            power[i + 1] = power[i] * base;
            geomSum[i + 1] = geomSum[i] * base + 1;
            preX[i + 1] = preX[i] * base + points[i].x;
            preY[i + 1] = preY[i] * base + points[i].y;
            revX[i + 1] = revX[i] * base + points[total - 1 - i].x;
            revY[i + 1] = revY[i] * base + points[total - 1 - i].y;
        }
        segTree.resize(total * 2);
        for (int i = 0; i < total; ++i) segTree[total + i].fill(i);
        for (int i = total - 1; i > 0; --i) segTree[i] = mergeMin(segTree[i * 2], segTree[i * 2 + 1]);
    }

    Point halfPoint(const HalfPoly &poly, int pos) const {
        if (poly.hasA && pos == 0) return poly.a;
        int offset = poly.hasA ? 1 : 0, innerCount = poly.right - poly.left + 1;
        if (pos < offset + innerCount) return points[poly.left + pos - offset];
        return poly.b;
    }

    HalfPoly makeHalf(ll start) const {
        HalfPoly poly;
        poly.a = pointAtDist(start);
        poly.b = pointAtDist(start + half);
        poly.left = upper_bound(dist.begin(), dist.end(), start) - dist.begin();
        poly.right = lower_bound(dist.begin(), dist.end(), start + half) - dist.begin() - 1;
        poly.hasA = turn(poly.b, poly.a, points[poly.left]) != 0;
        poly.hasB = turn(points[poly.right], poly.b, poly.a) != 0;
        poly.len = poly.right - poly.left + 1 + poly.hasA + poly.hasB;
        array<int, 8> best = queryMin(poly.left, poly.right + 1);
        int offset = poly.hasA ? 1 : 0;
        for (int op = 0; op < 8; ++op) {
            int pos = offset + best[op] - poly.left;
            Point cur = transformPoint(halfPoint(poly, pos), op);
            if (poly.hasA && lessPoint(transformPoint(poly.a, op), cur)) {
                pos = 0;
                cur = transformPoint(poly.a, op);
            }
            if (poly.hasB && lessPoint(transformPoint(poly.b, op), cur)) pos = poly.len - 1;
            poly.anchor[op] = pos;
        }
        return poly;
    }

    HashVal mergeHash(const HashVal &a, const HashVal &b) const {
        return {a.x * power[b.len] + b.x,
                a.y * power[b.len] + b.y,
                b.revX * power[a.len] + a.revX,
                b.revY * power[a.len] + a.revY,
                a.len + b.len};
    }

    HashVal pointHash(Point p) const {
        return {(ull)p.x, (ull)p.y, (ull)p.x, (ull)p.y, 1};
    }

    HashVal rangeHash(int left, int right) const {
        int len = right - left;
        return {preX[right] - preX[left] * power[len],
                preY[right] - preY[left] * power[len],
                revX[total - left] - revX[total - right] * power[len],
                revY[total - left] - revY[total - right] * power[len],
                len};
    }

    HashVal sliceHash(const HalfPoly &poly, int start, int len) const {
        HashVal result = {0, 0, 0, 0, 0};
        if (len == 0) return result;
        int end = start + len, offset = poly.hasA ? 1 : 0;
        int innerCount = poly.right - poly.left + 1;
        int left = max(start, offset), right = min(end, offset + innerCount);
        if (poly.hasA && start == 0) result = mergeHash(result, pointHash(poly.a));
        if (left < right) result = mergeHash(result, rangeHash(poly.left + left - offset, poly.left + right - offset));
        if (poly.hasB && start <= offset + innerCount && offset + innerCount < end) result = mergeHash(result, pointHash(poly.b));
        return result;
    }

    HashVal reverseHash(HashVal value) const {
        swap(value.x, value.revX);
        swap(value.y, value.revY);
        return value;
    }

    pair<ull, ull> canonicalHash(const HalfPoly &poly, int op) const {
        int pos = poly.anchor[op], len = poly.len;
        HashVal value;
        if (dirSign[op] == 1) {
            value = mergeHash(sliceHash(poly, pos, len - pos), sliceHash(poly, 0, pos));
        } else {
            HashVal first = reverseHash(sliceHash(poly, 0, pos + 1));
            HashVal second = reverseHash(sliceHash(poly, pos + 1, len - pos - 1));
            value = mergeHash(first, second);
        }
        Point origin = transformPoint(halfPoint(poly, pos), op);
        ull hashX = xCoef[op] * value.x + yCoef[op] * value.y - (ull)origin.x * geomSum[len];
        ull hashY = zCoef[op] * value.x + wCoef[op] * value.y - (ull)origin.y * geomSum[len];
        return {hashX, hashY};
    }

    bool exactEqual(const HalfPoly &first, const HalfPoly &second, int op) const {
        int len = first.len, firstStart = first.anchor[0], secondStart = second.anchor[op];
        Point firstOrigin = halfPoint(first, firstStart);
        Point secondOrigin = transformPoint(halfPoint(second, secondStart), op);
        for (int i = 0; i < len; ++i) {
            int firstPos = (firstStart + i) % len;
            int secondPos = (secondStart + dirSign[op] * i + len) % len;
            Point a = halfPoint(first, firstPos);
            Point b = transformPoint(halfPoint(second, secondPos), op);
            if (a.x - firstOrigin.x != b.x - secondOrigin.x) return false;
            if (a.y - firstOrigin.y != b.y - secondOrigin.y) return false;
        }
        return true;
    }

    bool solve(int vertexCount) {
        n = vertexCount;
        total = n * 2;
        points.resize(total);
        for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
        for (int i = 0; i < n; ++i) points[i + n] = points[i];
        dist.resize(total + 1);
        area.resize(total + 1);
        for (int i = 0; i < total; ++i) {
            Point a = points[i], b = points[(i + 1) % total];
            dist[i + 1] = dist[i] + abs(a.x - b.x) + abs(a.y - b.y);
            area[i + 1] = area[i] + cross(a, b);
        }
        perimeter = dist[n];
        half = perimeter / 2;
        findCandidates();
        if (cuts.empty()) return false;
        validateCuts(0);
        validateCuts(1);
        bool hasValid = false;
        for (const Cut &cut : cuts) if (cut.valid) hasValid = true;
        if (!hasValid) return false;
        prepareCompare();
        for (const Cut &cut : cuts) {
            if (!cut.valid) continue;
            HalfPoly first = makeHalf(cut.pos), second = makeHalf(cut.pos + half);
            if (first.len != second.len) continue;
            pair<ull, ull> firstHash = canonicalHash(first, 0);
            for (int op = 0; op < 8; ++op) {
                if (firstHash != canonicalHash(second, op)) continue;
                if (exactEqual(first, second, op)) return true;
            }
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        Solver solver;
        cout << (solver.solve(n) ? "Yes" : "No") << '\n';
    }
    return 0;
}
