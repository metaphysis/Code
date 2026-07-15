// Space Invaders
// UVa ID: 12789
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;
    vector<char> touchTop, touchBottom;
    bool connected;

    DSU(int n) : parent(n), rankv(n, 0), touchTop(n, 0), touchBottom(n, 0), connected(false) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    void initNode(int id, bool top, bool bottom) {
        touchTop[id] = top;
        touchBottom[id] = bottom;
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rankv[ra] < rankv[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rankv[ra] == rankv[rb]) ++rankv[ra];
        touchTop[ra] = touchTop[ra] || touchTop[rb];
        touchBottom[ra] = touchBottom[ra] || touchBottom[rb];
        if (touchTop[ra] && touchBottom[ra]) connected = true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, s;
    while (cin >> r >> c >> s) {
        vector<string> grid(r);
        for (int i = 0; i < r; ++i) cin >> grid[i];

        vector<int> shots(s);
        for (int i = 0; i < s; ++i) cin >> shots[i];

        int n = r * c;
        DSU dsu(n);

        // 初始化所有初始禁用格子的节点信息并合并相邻
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '.') {
                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                }
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '.') {
                    int id = i * c + j;
                    if (j + 1 < c && grid[i][j + 1] == '.')
                        dsu.unite(id, i * c + (j + 1));
                    if (i + 1 < r && grid[i + 1][j] == '.')
                        dsu.unite(id, (i + 1) * c + j);
                }

        // 检查初始连通性
        bool initialBreach = false;
        for (int i = 0; i < r && !initialBreach; ++i)
            for (int j = 0; j < c && !initialBreach; ++j)
                if (grid[i][j] == '.') {
                    int root = dsu.find(i * c + j);
                    if (dsu.touchTop[root] && dsu.touchBottom[root])
                        initialBreach = true;
                }
        if (initialBreach) {
            cout << "0\n";    // 注意：输出数字 0，不是字母 O
            continue;
        }

        // 每列激活格子的行号集合
        vector< set<int> > colSets(c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '#')
                    colSets[j].insert(i);

        bool found = false;
        for (int k = 0; k < s; ++k) {
            int a = shots[k];
            int j = abs(a) - 1;

            if (a > 0) { // 外星人：从北向南
                if (!colSets[j].empty()) {
                    int i = *colSets[j].begin();
                    colSets[j].erase(colSets[j].begin());
                    grid[i][j] = '.';

                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                    if (dsu.touchTop[id] && dsu.touchBottom[id])
                        dsu.connected = true;

                    const int dx[4] = {-1, 1, 0, 0};
                    const int dy[4] = {0, 0, -1, 1};
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && grid[ni][nj] == '.')
                            dsu.unite(id, ni * c + nj);
                    }

                    if (dsu.connected) {
                        cout << (k + 1) << '\n';
                        found = true;
                        break;
                    }
                }
            } else { // Nostalgia for Infinity：从南向北
                if (!colSets[j].empty()) {
                    int i = *colSets[j].rbegin();
                    colSets[j].erase(prev(colSets[j].end()));
                    grid[i][j] = '.';

                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                    if (dsu.touchTop[id] && dsu.touchBottom[id])
                        dsu.connected = true;

                    const int dx[4] = {-1, 1, 0, 0};
                    const int dy[4] = {0, 0, -1, 1};
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && grid[ni][nj] == '.')
                            dsu.unite(id, ni * c + nj);
                    }

                    if (dsu.connected) {
                        cout << -(k + 1) << '\n';
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found) cout << "X\n";
    }
    return 0;
}
