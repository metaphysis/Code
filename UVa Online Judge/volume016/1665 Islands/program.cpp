// Islands
// UVa ID: 1665
// Verdict: Accepted
// Submission Date: 2025-11-22
// UVa Run Time: 0.680s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

struct Cell {
    int height, x, y;
    bool operator<(const Cell& other) const {
        return height > other.height;
    }
};

vector<int> parent;

int findSet(int x) {
    return parent[x] == x ? x : parent[x] = findSet(parent[x]);
}

bool unionSet(int a, int b) {
    int ra = findSet(a), rb = findSet(b);
    if (ra != rb) {
        parent[ra] = rb;
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Z;
    cin >> Z;
    while (Z--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> height(n, vector<int>(m));
        vector<Cell> cells;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                cin >> height[i][j];
                cells.push_back({height[i][j], i, j});
            }
        sort(cells.begin(), cells.end());

        int T;
        cin >> T;
        vector<int> queries(T);
        for (int i = 0; i < T; i++) cin >> queries[i];

        vector<int> idx(T);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return queries[a] > queries[b];
        });

        parent.resize(n * m);
        iota(parent.begin(), parent.end(), 0);
        vector<bool> added(n * m, false);

        vector<int> result(T);
        int cur = 0, regions = 0;
        for (int i : idx) {
            int seaLevel = queries[i];
            while (cur < cells.size() && cells[cur].height > seaLevel) {
                int x = cells[cur].x, y = cells[cur].y;
                int id = x * m + y;
                added[id] = true;
                regions++;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && added[nx * m + ny])
                        if (unionSet(id, nx * m + ny)) regions--;
                }
                cur++;
            }
            result[i] = regions;
        }

        // 虽然题目描述中输出约束是间隔输出空格，但是在线测试数据要求每个数值后都输出一个空格
        for (int i = 0; i < T; i++)
            cout << result[i] << ' ';
        cout << "\n";
    }
    return 0;
}
