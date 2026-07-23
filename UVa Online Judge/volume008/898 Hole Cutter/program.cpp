// Hole Cutter
// UVa ID: 898
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Pt { int x, y; Pt(int a = 0, int b = 0): x(a), y(b) {} };
struct Seg { Pt s, e; Seg(Pt a = Pt(), Pt b = Pt()): s(a), e(b) {} };

int wall[205][205][4];
vector<int> xs, ys;
int parent[205 * 205], weight[205 * 205];

int relabelX(int x) { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); }
int relabelY(int y) { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); }

Seg relabelSeg(Seg seg) {
    seg.s.x = relabelX(seg.s.x);
    seg.e.x = relabelX(seg.e.x);
    seg.s.y = relabelY(seg.s.y);
    seg.e.y = relabelY(seg.e.y);
    return seg;
}

int findRoot(int x) { return parent[x] == x ? x : parent[x] = findRoot(parent[x]); }

int mergeSet(int x, int y) {
    x = findRoot(x), y = findRoot(y);
    if (x == y) return 0;
    if (weight[x] > weight[y]) { weight[x] += weight[y]; parent[y] = x; }
    else { weight[y] += weight[x]; parent[x] = y; }
    return 1;
}

void initUnionFind(int n) {
    for (int i = 0; i <= n; ++i) parent[i] = i, weight[i] = 1;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void tryMerge(int id, int nx, int ny, int maxX, int maxY, int wallDir, bool requireWall) {
    if (nx < 0 || nx >= maxX || ny < 0 || ny >= maxY) return;
    int nid = nx * maxY + ny;
    bool hasWall = wall[nx][ny][wallDir];
    if (requireWall) {
        if (hasWall && findRoot(nid) != findRoot(0)) mergeSet(id, nid);
    } else {
        if (!hasWall) mergeSet(id, nid);
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        vector<Seg> segs(n);
        xs.clear(); ys.clear();
        for (int i = 0; i < n; ++i) {
            int xa, ya, xb, yb;
            scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
            ++xa, ++ya, ++xb, ++yb;
            segs[i] = Seg(Pt(xa, ya), Pt(xb, yb));
            xs.push_back(xa); xs.push_back(xb);
            ys.push_back(ya); ys.push_back(yb);
        }
        xs.push_back(0); ys.push_back(0);
        xs.push_back(10000); ys.push_back(10000);
        sort(xs.begin(), xs.end()); sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        memset(wall, 0, sizeof(wall));
        for (int i = 0; i < n; ++i) {
            segs[i] = relabelSeg(segs[i]);
            if (segs[i].s.x == segs[i].e.x) {
                int l = min(segs[i].s.y, segs[i].e.y);
                int r = max(segs[i].s.y, segs[i].e.y);
                int x = segs[i].s.x;
                for (int j = l; j < r; ++j)
                    wall[x][j][1] = wall[x - 1][j][0] = 1;
            } else {
                int l = min(segs[i].s.x, segs[i].e.x);
                int r = max(segs[i].s.x, segs[i].e.x);
                int y = segs[i].s.y;
                for (int j = l; j < r; ++j)
                    wall[j][y][3] = wall[j][y - 1][2] = 1;
            }
        }
        int maxX = (int)xs.size(), maxY = (int)ys.size();
        initUnionFind(maxX * maxY);
        for (int i = 0; i < maxX; ++i)
            for (int j = 0; j < maxY; ++j) {
                int id = i * maxY + j;
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= 0 && ni < maxX && nj >= 0 && nj < maxY) {
                        int nid = ni * maxY + nj;
                        if (wall[i][j][d] == 0) mergeSet(id, nid);
                    }
                }
            }
        int external = findRoot(0);
        for (int i = 0; i < maxX; ++i)
            for (int j = 0; j < maxY; ++j) {
                int id = i * maxY + j;
                if (findRoot(id) == external) continue;
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni < 0 || ni >= maxX || nj < 0 || nj >= maxY) continue;
                    int nid = ni * maxY + nj;
                    if (wall[i][j][d] == 1 && findRoot(nid) != external)
                        mergeSet(id, nid);
                }
            }
        set<int> roots;
        for (int i = 0; i < maxX; ++i)
            for (int j = 0; j < maxY; ++j) {
                int r = findRoot(i * maxY + j);
                if (r != external) roots.insert(r);
            }
        printf("%d\n", (int)roots.size());
    }
    return 0;
}
