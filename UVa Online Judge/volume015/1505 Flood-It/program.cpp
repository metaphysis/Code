// Flood-It
// UVa ID: 1505
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>
#include <set>
using namespace std;

int N;
int board[8][8];
bool in_region[8][8];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

// 计算当前连通块，并标记在 in_region 中
void compute_region() {
    bool visited[8][8] = {false};
    vector<pair<int, int>> q;
    int base_color = board[0][0];
    q.push_back({0, 0});
    visited[0][0] = true;
    for (int i = 0; i < q.size(); i++) {
        int x = q[i].first, y = q[i].second;
        in_region[x][y] = true;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny] && board[nx][ny] == base_color) {
                visited[nx][ny] = true;
                q.push_back({nx, ny});
            }
        }
    }
}

// 估价函数：剩余颜色种类数
int heuristic() {
    set<int> colors;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!in_region[i][j])
                colors.insert(board[i][j]);
    return colors.size();
}

// 尝试染色
void apply_color(int color) {
    int old_color = board[0][0];
    // 先收集所有在 region 内的格子
    vector<pair<int, int>> region_cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (in_region[i][j])
                region_cells.push_back({i, j});
    // 把 region 内所有格子颜色改为 color
    for (auto& p : region_cells)
        board[p.first][p.second] = color;
    // 重新计算连通块
    memset(in_region, 0, sizeof(in_region));
    compute_region();
}

bool dfs(int depth, int max_depth) {
    int h = heuristic();
    if (h == 0) return true;
    if (depth + h > max_depth) return false;

    // 保存当前状态
    int old_board[8][8];
    bool old_in_region[8][8];
    memcpy(old_board, board, sizeof(board));
    memcpy(old_in_region, in_region, sizeof(in_region));

    for (int c = 0; c < 6; c++) {
        if (c == board[0][0]) continue; // 同色无变化
        apply_color(c);
        // 如果连通块没变化，跳过
        bool changed = false;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (old_in_region[i][j] != in_region[i][j]) {
                    changed = true;
                    break;
                }
        if (!changed) {
            memcpy(board, old_board, sizeof(board));
            memcpy(in_region, old_in_region, sizeof(in_region));
            continue;
        }
        if (dfs(depth + 1, max_depth)) return true;
        // 恢复状态
        memcpy(board, old_board, sizeof(board));
        memcpy(in_region, old_in_region, sizeof(in_region));
    }
    return false;
}

int main() {
    while (cin >> N && N != 0) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> board[i][j];
        memset(in_region, 0, sizeof(in_region));
        compute_region();
        if (heuristic() == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int max_depth = 1; ; max_depth++) {
            if (dfs(0, max_depth)) {
                cout << max_depth << endl;
                break;
            }
        }
    }
    return 0;
}
