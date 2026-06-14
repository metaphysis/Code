// Building Bridges
// UVa ID: 1018
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXB = 10005;

int r, c;
char grid[MAXN][MAXN];
int comp[MAXN][MAXN];
int compCount;

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

struct Building {
    int minRow, maxRow, minCol, maxCol;
    vector<pair<int,int>> cells;
} bld[MAXB];

void floodFill(int x, int y, int id) {
    if (x < 0 || x >= r || y < 0 || y >= c) return;
    if (grid[x][y] != '#') return;
    if (comp[x][y] != -1) return;
    comp[x][y] = id;
    bld[id].cells.push_back({x, y});
    bld[id].minRow = min(bld[id].minRow, x);
    bld[id].maxRow = max(bld[id].maxRow, x);
    bld[id].minCol = min(bld[id].minCol, y);
    bld[id].maxCol = max(bld[id].maxCol, y);
    for (int d = 0; d < 8; d++) floodFill(x + dx[d], y + dy[d], id);
}

struct Bridge {
    int u, v, len;
    bool operator<(const Bridge& other) const { return len < other.len; }
};

vector<Bridge> bridges;
int parent[MAXB];

int findSet(int x) {
    if (parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

bool unionSet(int x, int y) {
    int rx = findSet(x), ry = findSet(y);
    if (rx == ry) return false;
    parent[rx] = ry;
    return true;
}

void solve(int cityNum) {
    memset(comp, -1, sizeof(comp));
    compCount = 0;
    
    for (int i = 0; i < MAXB; i++) {
        bld[i].minRow = bld[i].minCol = 1e9;
        bld[i].maxRow = bld[i].maxCol = -1e9;
        bld[i].cells.clear();
    }
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (grid[i][j] == '#' && comp[i][j] == -1)
                floodFill(i, j, compCount++);
    
    if (compCount < 2) {
        printf("City %d\nNo bridges are needed.\n", cityNum);
        return;
    }
    
    bridges.clear();
    
    for (int i = 0; i < compCount; i++) {
        for (int j = i + 1; j < compCount; j++) {
            int minLen = 1e9;
            for (auto& cellA : bld[i].cells) {
                for (auto& cellB : bld[j].cells) {
                    int dr = abs(cellA.first - cellB.first);
                    int dc = abs(cellA.second - cellB.second);
                    if (dr <= 1) minLen = min(minLen, dc - 1);
                    if (dc <= 1) minLen = min(minLen, dr - 1);
                }
            }
            if (minLen < 1e9) bridges.push_back({i, j, minLen});
        }
    }
    
    sort(bridges.begin(), bridges.end());
    for (int i = 0; i < compCount; i++) parent[i] = i;
    
    int totalLen = 0, used = 0;
    for (auto& b : bridges)
        if (unionSet(b.u, b.v)) {
            totalLen += b.len;
            used++;
        }
    
    int groups = 0;
    for (int i = 0; i < compCount; i++) if (findSet(i) == i) groups++;
    
    if (used == 0) {
        printf("City %d\nNo bridges are possible.\n", cityNum);
        if (groups > 1) printf("%d disconnected groups\n", groups);
    } else {
        printf("City %d\n", cityNum);
        if (used == 1) printf("1 bridge of total length %d\n", totalLen);
        else printf("%d bridges of total length %d\n", used, totalLen);
        if (groups > 1) printf("%d disconnected groups\n", groups);
    }
}

int main() {
    int cityNum = 0;
    while (scanf("%d %d", &r, &c) == 2) {
        if (r == 0 && c == 0) break;
        for (int i = 0; i < r; i++) scanf("%s", grid[i]);
        if (cityNum > 0) printf("\n");
        solve(++cityNum);
    }
    return 0;
}
