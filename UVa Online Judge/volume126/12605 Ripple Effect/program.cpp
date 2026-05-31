// Ripple Effect
// UVa ID: 12605
// Verdict: Accepted
// Submission Date: 2026-06-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方向数组：上、右、下、左
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};
// 对应 descr 的位：UP=1, RIGHT=2, DOWN=4, LEFT=8
const int dirMask[4] = {1, 2, 4, 8};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int R, C;
        cin >> R >> C;
        
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) 
            cin >> grid[i];
        
        vector<vector<int>> descr(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                cin >> descr[i][j];
        
        // 并查集：连通分量
        vector<int> parent(R * C);
        for (int i = 0; i < R * C; ++i) parent[i] = i;
        
        function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        auto unite = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa != pb) parent[pa] = pb;
        };
        
        // 根据 descr 合并连通格子
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                int val = descr[r][c];
                int idx = r * C + c;
                // 检查四个方向
                for (int d = 0; d < 4; ++d) {
                    if (val & dirMask[d]) { // 有连通
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                            int nidx = nr * C + nc;
                            unite(idx, nidx);
                        }
                    }
                }
            }
        }
        
        // 收集每个连通分量的格子
        map<int, vector<pair<int, int>>> components;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                int root = find(r * C + c);
                components[root].emplace_back(r, c);
            }
        }
        
        bool valid = true;
        
        // 检查每个多联骨牌
        for (auto& [root, cells] : components) {
            int sz = cells.size();
            vector<int> nums;
            for (auto& [r, c] : cells) {
                nums.push_back(grid[r][c] - '0');
            }
            sort(nums.begin(), nums.end());
            // 检查是否是 1..sz 的排列
            for (int i = 0; i < sz; ++i) {
                if (nums[i] != i + 1) { valid = false; break; }
            }
            if (!valid) break;
        }
        
        if (!valid) {
            cout << "invalid\n";
            continue;
        }
        
        // 检查行约束
        for (int r = 0; r < R; ++r) {
            // 对每个数字 1..8
            for (int num = 1; num <= 8; ++num) {
                vector<int> cols;
                for (int c = 0; c < C; ++c) {
                    if (grid[r][c] - '0' == num)
                        cols.push_back(c);
                }
                // 检查间隔
                for (size_t i = 1; i < cols.size(); ++i) {
                    int gap = cols[i] - cols[i - 1] - 1;
                    if (gap < num) { valid = false; break; }
                }
                if (!valid) break;
            }
            if (!valid) break;
        }
        
        if (!valid) {
            cout << "invalid\n";
            continue;
        }
        
        // 检查列约束
        for (int c = 0; c < C; ++c) {
            for (int num = 1; num <= 8; ++num) {
                vector<int> rows;
                for (int r = 0; r < R; ++r) {
                    if (grid[r][c] - '0' == num)
                        rows.push_back(r);
                }
                for (size_t i = 1; i < rows.size(); ++i) {
                    int gap = rows[i] - rows[i - 1] - 1;
                    if (gap < num) { valid = false; break; }
                }
                if (!valid) break;
            }
            if (!valid) break;
        }
        
        cout << (valid ? "valid" : "invalid") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
