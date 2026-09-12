#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Wall {
    Point a, b;
};

long long cross(Point a, Point b, Point c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

bool onSeg(Point a, Point b, Point p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segHit(Point a, Point b, Point c, Point d) {
    long long c1, c2, c3, c4;
    c1 = cross(a, b, c);
    c2 = cross(a, b, d);
    c3 = cross(c, d, a);
    c4 = cross(c, d, b);
    if (c1 == 0 && onSeg(a, b, c)) return true;
    if (c2 == 0 && onSeg(a, b, d)) return true;
    if (c3 == 0 && onSeg(c, d, a)) return true;
    if (c4 == 0 && onSeg(c, d, b)) return true;
    return ((c1 > 0 && c2 < 0) || (c1 < 0 && c2 > 0)) && ((c3 > 0 && c4 < 0) || (c3 < 0 && c4 > 0));
}

int getCell(int v, int r) {
    if (v >= 0) return v / r;
    return -((-v + r - 1) / r);
}

long long getKey(int x, int y) {
    return static_cast<long long>((static_cast<unsigned long long>(static_cast<unsigned int>(x)) << 32) | static_cast<unsigned int>(y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    while (testNum--) {
        int s, r, w, p;
        cin >> s >> r >> w >> p;
        vector<Point> sensors(s);
        unordered_map<long long, vector<int>> grid;
        grid.reserve(s * 2 + 1);
        for (int i = 0; i < s; i++) {
            cin >> sensors[i].x >> sensors[i].y;
            int cx, cy;
            cx = getCell(sensors[i].x, r);
            cy = getCell(sensors[i].y, r);
            grid[getKey(cx, cy)].push_back(i);
        }
        vector<Wall> walls(w);
        for (int i = 0; i < w; i++) cin >> walls[i].a.x >> walls[i].a.y >> walls[i].b.x >> walls[i].b.y;
        for (int i = 0; i < p; i++) {
            Point product;
            cin >> product.x >> product.y;
            vector<Point> result;
            int cx, cy;
            cx = getCell(product.x, r);
            cy = getCell(product.y, r);
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    auto it = grid.find(getKey(cx + dx, cy + dy));
                    if (it == grid.end()) continue;
                    for (int id : it->second) {
                        long long px, py, dist2;
                        px = sensors[id].x - product.x;
                        py = sensors[id].y - product.y;
                        dist2 = px * px + py * py;
                        if (dist2 > 1LL * r * r) continue;
                        int hit = 0;
                        for (const Wall &wall : walls) {
                            if (segHit(sensors[id], product, wall.a, wall.b)) hit++;
                        }
                        if (hit > r) continue;
                        int remain = r - hit;
                        if (dist2 <= 1LL * remain * remain) result.push_back(sensors[id]);
                    }
                }
            }
            sort(result.begin(), result.end(), [](const Point &a, const Point &b) {
                if (a.x != b.x) return a.x < b.x;
                return a.y < b.y;
            });
            cout << result.size();
            for (const Point &point : result) cout << " (" << point.x << "," << point.y << ")";
            cout << '\n';
        }
    }
    return 0;
}
