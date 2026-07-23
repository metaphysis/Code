// Snake
// UVa ID: 841
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int bfs(int R, int C, const vector<string>& grid, const vector<pair<int,int>>& eggs) {
    int E = eggs.size();
    if (E == 0) return 0;
    vector<vector<int>> eggIdx(R, vector<int>(C, -1));
    for (int i = 0; i < E; ++i) eggIdx[eggs[i].first][eggs[i].second] = i;
    vector<int> startBody;
    startBody.push_back(0 * C + 0);          // 头部在索引0，尾部在末尾
    int startMask = 0;
    queue<tuple<vector<int>, int, int>> q;
    map<pair<vector<int>, int>, bool> visited;
    visited[{startBody, startMask}] = true;
    q.push({startBody, startMask, 0});
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        vector<int> body = get<0>(cur);
        int mask = get<1>(cur);
        int steps = get<2>(cur);
        if (mask == (1 << E) - 1) return steps;
        int head = body[0];
        int r = head / C, c = head % C;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == 'x') continue;
            int newHead = nr * C + nc;
            // 关键修正：不允许移动到身体的任何位置（包括尾部）
            bool inBody = false;
            for (int pos : body) if (pos == newHead) { inBody = true; break; }
            if (inBody) continue;
            int egg = eggIdx[nr][nc];
            bool eat = (egg != -1 && !(mask & (1 << egg)));
            int newMask = mask;
            vector<int> newBody;
            newBody.push_back(newHead);          // 新头
            if (eat) {
                newMask = mask | (1 << egg);
                newBody.insert(newBody.end(), body.begin(), body.end()); // 保留全部旧身体
            } else {
                newBody.insert(newBody.end(), body.begin(), body.end() - 1); // 去掉尾部
            }
            auto key = make_pair(newBody, newMask);
            if (visited.find(key) == visited.end()) {
                visited[key] = true;
                q.push({newBody, newMask, steps + 1});
            }
        }
    }
    return -1;
}

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int R;
        cin >> R;
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) cin >> grid[i];
        int C = grid[0].size();
        vector<pair<int,int>> eggs;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (grid[i][j] == 'o') eggs.push_back({i, j});
        int ans = bfs(R, C, grid, eggs);
        if (caseNo > 1) cout << "\n";
        if (ans == -1) cout << "NO\n";
        else cout << ans << "\n";
    }
    return 0;
}
