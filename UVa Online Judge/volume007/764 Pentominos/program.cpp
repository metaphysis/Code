// Pentominos
// UVa ID: 764
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.900s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

// 所有五连方朝向的坐标偏移（相对于锚点）
vector<vector<pair<int,int>>> allOrients;

// 生成 12 种五连方的所有不同朝向
void generateShapes() {
    set<vector<pair<int,int>>> uniqueKeys;
    vector<pair<int,int>> cells;

    function<void(int)> dfsGen = [&](int step) {
        if (step == 5) {
            int minR = INT_MAX, minC = INT_MAX;
            for (auto &p : cells) { minR = min(minR, p.first); minC = min(minC, p.second); }
            vector<pair<int,int>> norm;
            for (auto &p : cells) norm.push_back({p.first - minR, p.second - minC});
            sort(norm.begin(), norm.end());

            int trans[8][2][2] = {
                {{1,0},{0,1}}, {{1,0},{0,-1}}, {{-1,0},{0,1}}, {{-1,0},{0,-1}},
                {{0,1},{1,0}}, {{0,1},{-1,0}}, {{0,-1},{1,0}}, {{0,-1},{-1,0}}
            };
            vector<pair<int,int>> best = norm;
            for (int t = 0; t < 8; ++t) {
                vector<pair<int,int>> cur;
                for (auto &p : norm) {
                    int nr = p.first * trans[t][0][0] + p.second * trans[t][0][1];
                    int nc = p.first * trans[t][1][0] + p.second * trans[t][1][1];
                    cur.push_back({nr, nc});
                }
                int mr = INT_MAX, mc = INT_MAX;
                for (auto &p : cur) { mr = min(mr, p.first); mc = min(mc, p.second); }
                for (auto &p : cur) { p.first -= mr; p.second -= mc; }
                sort(cur.begin(), cur.end());
                if (cur < best) best = cur;
            }
            uniqueKeys.insert(best);
            return;
        }

        set<pair<int,int>> neighbors;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        for (auto &p : cells) {
            for (int d = 0; d < 4; ++d) {
                int nr = p.first + dr[d], nc = p.second + dc[d];
                if (find(cells.begin(), cells.end(), make_pair(nr, nc)) == cells.end())
                    neighbors.insert({nr, nc});
            }
        }
        for (auto &np : neighbors) {
            cells.push_back(np);
            dfsGen(step + 1);
            cells.pop_back();
        }
    };

    cells.push_back({0, 0});
    dfsGen(1);

    // 从 uniqueKeys 提取所有朝向
    for (auto &key : uniqueKeys) {
        set<vector<pair<int,int>>> seen;
        int trans[8][2][2] = {
            {{1,0},{0,1}}, {{1,0},{0,-1}}, {{-1,0},{0,1}}, {{-1,0},{0,-1}},
            {{0,1},{1,0}}, {{0,1},{-1,0}}, {{0,-1},{1,0}}, {{0,-1},{-1,0}}
        };
        for (int t = 0; t < 8; ++t) {
            vector<pair<int,int>> cur;
            for (auto &p : key) {
                int nr = p.first * trans[t][0][0] + p.second * trans[t][0][1];
                int nc = p.first * trans[t][1][0] + p.second * trans[t][1][1];
                cur.push_back({nr, nc});
            }
            int mr = INT_MAX, mc = INT_MAX;
            for (auto &p : cur) { mr = min(mr, p.first); mc = min(mc, p.second); }
            for (auto &p : cur) { p.first -= mr; p.second -= mc; }
            sort(cur.begin(), cur.end());
            if (seen.insert(cur).second) allOrients.push_back(cur);
        }
    }
}

// 放置结构：位掩码和覆盖格子索引列表
struct Placement {
    ull mask;
    vector<int> cells;
};

vector<Placement> placements;   // 当前测试用例的所有合法放置
vector<int> cover[64];          // cover[pos] 存储能覆盖 pos 的放置索引
char board[64];                 // 棋盘字符（0 表示空格，'*' 表示阻塞）

// 连通性剪枝：剩余空格每个连通分量大小必须为 5 的倍数
bool checkConnectivity(ull occupied) {
    bool vis[64] = {};
    for (int i = 0; i < 64; ++i) {
        if (!(occupied >> i & 1) && !vis[i]) {
            int cnt = 0;
            queue<int> q;
            q.push(i); vis[i] = true;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                ++cnt;
                int r = v / 8, c = v % 8;
                int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
                        int nid = nr * 8 + nc;
                        if (!(occupied >> nid & 1) && !vis[nid]) {
                            vis[nid] = true;
                            q.push(nid);
                        }
                    }
                }
            }
            if (cnt % 5 != 0) return false;
        }
    }
    return true;
}

// 深度优先搜索
bool dfs(ull occupied, char ch) {
    int left = 64 - __builtin_popcountll(occupied);
    if (left == 0) return true;
    if (left % 5 != 0) return false;
    if (!checkConnectivity(occupied)) return false;

    // 选择候选放置最少的空格（MRV）
    int bestPos = -1, bestCnt = INT_MAX;
    for (int i = 0; i < 64; ++i) {
        if ((occupied >> i & 1) == 0) {
            int cnt = 0;
            for (int pid : cover[i]) {
                if ((placements[pid].mask & occupied) == 0) ++cnt;
            }
            if (cnt == 0) return false;
            if (cnt < bestCnt) { bestCnt = cnt; bestPos = i; }
        }
    }

    // 尝试所有覆盖 bestPos 的放置
    for (int pid : cover[bestPos]) {
        if (placements[pid].mask & occupied) continue;
        // 放置该块，分配当前字符 ch
        ull newOcc = occupied | placements[pid].mask;
        for (int idx : placements[pid].cells) board[idx] = ch;
        if (dfs(newOcc, ch + 1)) return true;
        // 回溯
        for (int idx : placements[pid].cells) board[idx] = 0;
    }
    return false;
}

int main() {
    generateShapes(); // 预生成所有五连方朝向

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        ull occupied = 0;
        for (int i = 0; i < 64; ++i) board[i] = 0;

        // 读入 4 个阻塞格（坐标 1~8 转为 0~7）
        for (int i = 0; i < 4; ++i) {
            int x, y;
            cin >> x >> y;
            int idx = (x - 1) * 8 + (y - 1);
            occupied |= 1ULL << idx;
            board[idx] = '*';
        }

        // 生成当前棋盘的所有合法放置（不覆盖阻塞格）
        placements.clear();
        for (int i = 0; i < 64; ++i) cover[i].clear();

        for (auto &coords : allOrients) {
            for (int r = 0; r < 8; ++r) {
                for (int c = 0; c < 8; ++c) {
                    ull mask = 0;
                    vector<int> cells;
                    bool ok = true;
                    for (auto &p : coords) {
                        int nr = r + p.first, nc = c + p.second;
                        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) { ok = false; break; }
                        int idx = nr * 8 + nc;
                        if (occupied & (1ULL << idx)) { ok = false; break; }
                        mask |= 1ULL << idx;
                        cells.push_back(idx);
                    }
                    if (ok) {
                        int pid = placements.size();
                        placements.push_back({mask, cells});
                        for (int idx : cells) cover[idx].push_back(pid);
                    }
                }
            }
        }

        if (dfs(occupied, 'a')) {
            // 输出棋盘
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j)
                    cout << board[i * 8 + j];
                cout << '\n';
            }
        } else {
            cout << "No solution.\n";
        }
        if (caseNo != T) cout << '\n'; // 两组输出间空行
    }
    return 0;
}
