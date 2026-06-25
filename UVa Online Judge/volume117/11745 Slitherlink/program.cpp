// Slitherlink
// UVa ID: 11745
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 并查集
class DSU {
public:
    vector<int> parent, rankv;
    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rankv[rx] < rankv[ry]) parent[rx] = ry;
        else if (rankv[rx] > rankv[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rankv[rx]++; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int R, C;
        cin >> R >> C;
        string dummy;
        getline(cin, dummy); // 消耗 R C 后面的换行

        int rows = 2 * R + 1, cols = 2 * C + 1;
        vector<string> grid(rows);
        for (int i = 0; i < rows; ++i) {
            getline(cin, grid[i]);
            // 去除可能的 Windows 换行符
            if (!grid[i].empty() && grid[i].back() == '\r') grid[i].pop_back();
        }

        bool valid = true;

        // 1. 检查数字约束
        for (int i = 1; i < rows; i += 2) {
            for (int j = 1; j < cols; j += 2) {
                char ch = grid[i][j];
                if (ch == ' ') continue;
                int k = ch - '0';
                int cnt = 0;
                if (i - 1 >= 0 && grid[i-1][j] == '-') cnt++;
                if (i + 1 < rows && grid[i+1][j] == '-') cnt++;
                if (j - 1 >= 0 && grid[i][j-1] == '|') cnt++;
                if (j + 1 < cols && grid[i][j+1] == '|') cnt++;
                if (cnt != k) { valid = false; break; }
            }
            if (!valid) break;
        }
        if (!valid) { cout << "Invalid\n"; continue; }

        int vertexRows = R + 1, vertexCols = C + 1;
        int totalV = vertexRows * vertexCols;
        vector<int> deg(totalV, 0);
        DSU dsu(totalV);

        // 2. 构建图并统计度数
        // 水平边：行 i 为偶数（0,2,...,2R），列 j 为奇数（1,3,...,2C-1）
        for (int i = 0; i <= 2 * R; i += 2) {
            for (int j = 1; j <= 2 * C - 1; j += 2) {
                if (grid[i][j] == '-') {
                    int row = i / 2;
                    int col1 = (j - 1) / 2;
                    int col2 = (j + 1) / 2;
                    int v1 = row * vertexCols + col1;
                    int v2 = row * vertexCols + col2;
                    deg[v1]++; deg[v2]++;
                    dsu.unite(v1, v2);
                }
            }
        }
        // 垂直边：行 i 为奇数（1,3,...,2R-1），列 j 为偶数（0,2,...,2C）
        // 注意：必须包含列 2C（最右边一列）
        for (int i = 1; i <= 2 * R - 1; i += 2) {
            for (int j = 0; j <= 2 * C; j += 2) {
                if (grid[i][j] == '|') {
                    int col = j / 2;
                    int row1 = (i - 1) / 2;
                    int row2 = (i + 1) / 2;
                    int v1 = row1 * vertexCols + col;
                    int v2 = row2 * vertexCols + col;
                    deg[v1]++; deg[v2]++;
                    dsu.unite(v1, v2);
                }
            }
        }

        // 3. 检查度数及连通性
        int firstDeg2 = -1;
        for (int v = 0; v < totalV; ++v) {
            if (deg[v] != 0 && deg[v] != 2) { valid = false; break; }
            if (deg[v] == 2) {
                if (firstDeg2 == -1) firstDeg2 = v;
            }
        }
        if (valid) {
            if (firstDeg2 == -1) {
                valid = false; // 没有环
            } else {
                int root = dsu.find(firstDeg2);
                for (int v = 0; v < totalV; ++v) {
                    if (deg[v] == 2 && dsu.find(v) != root) {
                        valid = false; break;
                    }
                }
            }
        }

        cout << (valid ? "Valid" : "Invalid") << '\n';
    }
    return 0;
}
