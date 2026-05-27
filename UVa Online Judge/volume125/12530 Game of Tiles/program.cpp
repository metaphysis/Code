// Game of Tiles
// UVa ID: 12530
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int R, C;
vector<string> board;
vector<vector<int>> leftId;
vector<vector<int>> rightId;
vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<bool> vis;

int leftCnt, rightCnt;

bool dfs(int u) {
    if (vis[u]) return false;
    vis[u] = true;
    for (int v : adj[u]) {
        if (matchR[v] == -1 || dfs(matchR[v])) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int solve() {
    // 给白格编号
    leftId.assign(R, vector<int>(C, -1));
    rightId.assign(R, vector<int>(C, -1));
    leftCnt = rightCnt = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] == '.') {
                if ((i + j) % 2 == 0)
                    leftId[i][j] = leftCnt++;
                else
                    rightId[i][j] = rightCnt++;
            }
        }
    }
    
    // 建图
    adj.assign(leftCnt, vector<int>());
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] == '.' && (i + j) % 2 == 0) {
                int u = leftId[i][j];
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= 0 && ni < R && nj >= 0 && nj < C && board[ni][nj] == '.') {
                        int v = rightId[ni][nj];
                        adj[u].push_back(v);
                    }
                }
            }
        }
    }
    
    // 匈牙利算法求最大匹配
    matchL.assign(leftCnt, -1);
    matchR.assign(rightCnt, -1);
    for (int u = 0; u < leftCnt; ++u) {
        vis.assign(leftCnt, false);
        dfs(u);
    }
    
    // 统计匹配边数
    int matchSize = 0;
    for (int u = 0; u < leftCnt; ++u)
        if (matchL[u] != -1) matchSize++;
    
    // 如果最大匹配覆盖所有白格（完美匹配），后手胜
    if (matchSize * 2 == leftCnt + rightCnt)
        return 2;
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> R >> C) {
        board.resize(R);
        for (int i = 0; i < R; ++i)
            cin >> board[i];
        cout << solve() << '\n';
    }
    return 0;
}
