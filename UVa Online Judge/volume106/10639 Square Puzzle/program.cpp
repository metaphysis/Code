#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Placement {
    int id;
    array<unsigned long long, 3> mask;
};

struct State {
    int used;
    array<unsigned long long, 3> mask;
    bool operator == (const State &other) const {
        return used == other.used && mask == other.mask;
    }
};

struct StateHash {
    size_t operator () (const State &state) const {
        size_t res = state.used;
        for (int i = 0; i < 3; i++)
            res ^= state.mask[i] + 0x9e3779b97f4a7c15ULL + (res << 6) + (res >> 2);
        return res;
    }
};

int n, m, cellCnt;
long long areaSum;
array<unsigned long long, 3> fullMask;
vector<Placement> placements;
vector<vector<int>> candidates;
unordered_set<State, StateHash> badStates;

long long getArea2(const vector<Point> &poly) {
    long long sum = 0;
    int sz = poly.size();
    for (int i = 0; i < sz; i++)
        sum += 1LL * poly[i].x * poly[(i + 1) % sz].y - 1LL * poly[i].y * poly[(i + 1) % sz].x;
    return llabs(sum);
}

bool isInside(const vector<Point> &poly, int dx, int dy, long long px, long long py) {
    bool inside = false;
    int sz = poly.size();
    for (int i = 0; i < sz; i++) {
        Point a = poly[i], b = poly[(i + 1) % sz];
        long long ax = 6LL * (a.x + dx), ay = 6LL * (a.y + dy);
        long long bx = 6LL * (b.x + dx), by = 6LL * (b.y + dy);
        if ((ay > py) != (by > py)) {
            long long cross = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
            if ((cross > 0) == (by > ay)) inside = !inside;
        }
    }
    return inside;
}

array<unsigned long long, 3> getMask(const vector<Point> &poly, int dx, int dy) {
    array<unsigned long long, 3> mask{};
    int addX[4] = {3, 5, 3, 1};
    int addY[4] = {1, 3, 5, 3};
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < m; x++) {
            for (int t = 0; t < 4; t++) {
                long long px = 6LL * x + addX[t], py = 6LL * y + addY[t];
                if (isInside(poly, dx, dy, px, py)) {
                    int bit = (y * m + x) * 4 + t;
                    mask[bit / 64] |= 1ULL << (bit % 64);
                }
            }
        }
    }
    return mask;
}

bool canPlace(const Placement &placement, const array<unsigned long long, 3> &usedMask) {
    for (int i = 0; i < 3; i++)
        if (placement.mask[i] & usedMask[i]) return false;
    return true;
}

void addPiece(vector<Point> poly, int id) {
    set<array<unsigned long long, 3>> seen;
    for (int rot = 0; rot < 4; rot++) {
        int minX = INT_MAX, minY = INT_MAX;
        for (const Point &p : poly) {
            minX = min(minX, p.x);
            minY = min(minY, p.y);
        }
        vector<Point> cur = poly;
        int maxX = 0, maxY = 0;
        for (Point &p : cur) {
            p.x -= minX;
            p.y -= minY;
            maxX = max(maxX, p.x);
            maxY = max(maxY, p.y);
        }
        for (int dx = 0; dx <= m - maxX; dx++) {
            for (int dy = 0; dy <= m - maxY; dy++) {
                array<unsigned long long, 3> mask = getMask(cur, dx, dy);
                if (!seen.insert(mask).second) continue;
                int pos = placements.size();
                placements.push_back({id, mask});
                for (int bit = 0; bit < cellCnt; bit++)
                    if (mask[bit / 64] & (1ULL << (bit % 64))) candidates[bit].push_back(pos);
            }
        }
        for (Point &p : poly) {
            int x = p.x;
            p.x = -p.y;
            p.y = x;
        }
    }
}

bool dfs(int used, const array<unsigned long long, 3> &usedMask) {
    if (used == (1 << n) - 1) return usedMask == fullMask;
    State state{used, usedMask};
    if (badStates.count(state)) return false;
    int bestBit = -1, bestCnt = INT_MAX;
    for (int bit = 0; bit < cellCnt; bit++) {
        if (usedMask[bit / 64] & (1ULL << (bit % 64))) continue;
        int cnt = 0;
        for (int pos : candidates[bit]) {
            const Placement &placement = placements[pos];
            if (used & (1 << placement.id)) continue;
            if (canPlace(placement, usedMask)) cnt++;
        }
        if (cnt == 0) {
            badStates.insert(state);
            return false;
        }
        if (cnt < bestCnt) {
            bestCnt = cnt;
            bestBit = bit;
        }
    }
    if (bestBit == -1) {
        badStates.insert(state);
        return false;
    }
    for (int pos : candidates[bestBit]) {
        const Placement &placement = placements[pos];
        if (used & (1 << placement.id)) continue;
        if (!canPlace(placement, usedMask)) continue;
        array<unsigned long long, 3> nextMask = usedMask;
        for (int i = 0; i < 3; i++)
            nextMask[i] |= placement.mask[i];
        if (dfs(used | (1 << placement.id), nextMask)) return true;
    }
    badStates.insert(state);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    while (testCnt--) {
        cin >> n >> m;
        cellCnt = 4 * m * m;
        areaSum = 0;
        placements.clear();
        candidates.assign(cellCnt, {});
        badStates.clear();
        fullMask = {};
        for (int bit = 0; bit < cellCnt; bit++)
            fullMask[bit / 64] |= 1ULL << (bit % 64);
        vector<vector<Point>> pieces(n);
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            pieces[i].resize(k);
            for (int j = 0; j < k; j++)
                cin >> pieces[i][j].x >> pieces[i][j].y;
            areaSum += getArea2(pieces[i]);
        }
        if (areaSum != 2LL * m * m) {
            cout << "no\n";
            continue;
        }
        for (int i = 0; i < n; i++)
            addPiece(pieces[i], i);
        array<unsigned long long, 3> usedMask{};
        cout << (dfs(0, usedMask) ? "yes\n" : "no\n");
    }
    return 0;
}
