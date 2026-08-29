#include <bits/stdc++.h>
using namespace std;

struct Block { vector<pair<int,int>> cells; };

int N;
vector<string> grid, ans;
vector<vector<int>> belong;
vector<int> blockCol;
vector<pair<int,int>> emptyCells;
vector<Block> blocks;
vector<vector<vector<int>>> cellsToBlocks;
const int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool dfs(int left) {
    if (left == 0) return true;
    int r = -1, c = -1;
    for (auto &p : emptyCells) {
        if (belong[p.first][p.second] == -1) {
            r = p.first; c = p.second; break;
        }
    }
    if (r == -1) return left == 0;
    vector<int> cand = cellsToBlocks[r][c];
    vector<int> valid;
    for (int bid : cand) {
        bool ok = true;
        for (auto &p : blocks[bid].cells) {
            if (belong[p.first][p.second] != -1) { ok = false; break; }
        }
        if (ok) valid.push_back(bid);
    }
    sort(valid.begin(), valid.end(), [&](int a, int b) {
        return blocks[a].cells < blocks[b].cells;
    });
    for (int bid : valid) {
        Block &blk = blocks[bid];
        for (int col = 0; col < 3; ++col) {
            bool conflict = false;
            for (auto &p : blk.cells) {
                int x = p.first, y = p.second;
                for (int d = 0; d < 8 && !conflict; ++d) {
                    int nx = x + dirs[d][0], ny = y + dirs[d][1];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    int nb = belong[nx][ny];
                    if (nb != -1 && nb != bid && blockCol[nb] == col) {
                        conflict = true; break;
                    }
                }
            }
            if (conflict) continue;
            blockCol[bid] = col;
            for (auto &p : blk.cells) {
                belong[p.first][p.second] = bid;
                ans[p.first][p.second] = char('B' + col);
            }
            if (dfs(left - 5)) return true;
            for (auto &p : blk.cells) {
                belong[p.first][p.second] = -1;
                ans[p.first][p.second] = '.';
            }
            blockCol[bid] = -1;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N;
        grid.resize(N);
        for (int i = 0; i < N; ++i) cin >> grid[i];
        cout << "Case " << tc << ":";
        emptyCells.clear();
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
            if (grid[i][j] == '.') emptyCells.push_back({i, j});
        int total = (int)emptyCells.size();
        if (total % 5 != 0) { cout << " Not Possible!\n"; continue; }
        blocks.clear();
        cellsToBlocks.assign(N, vector<vector<int>>(N));
        for (int i = 1; i < N - 1; ++i) for (int j = 1; j < N - 1; ++j) {
            if (grid[i][j] != '.') continue;
            int ni[4] = {i-1, i+1, i, i};
            int nj[4] = {j, j, j-1, j+1};
            bool ok = true;
            for (int k = 0; k < 4; ++k) {
                if (grid[ni[k]][nj[k]] != '.') { ok = false; break; }
            }
            if (!ok) continue;
            Block blk;
            blk.cells.push_back({i, j});
            for (int k = 0; k < 4; ++k) blk.cells.push_back({ni[k], nj[k]});
            sort(blk.cells.begin(), blk.cells.end());
            int bid = (int)blocks.size();
            blocks.push_back(blk);
            for (auto &p : blk.cells) cellsToBlocks[p.first][p.second].push_back(bid);
        }
        bool anyEmpty = false;
        for (auto &p : emptyCells) {
            if (cellsToBlocks[p.first][p.second].empty()) { anyEmpty = true; break; }
        }
        if (anyEmpty) { cout << " Not Possible!\n"; continue; }
        belong.assign(N, vector<int>(N, -1));
        blockCol.assign(blocks.size(), -1);
        ans = grid;
        if (dfs(total)) {
            cout << '\n';
            for (int i = 0; i < N; ++i) cout << ans[i] << '\n';
        } else {
            cout << " Not Possible!\n";
        }
    }
    return 0;
}
