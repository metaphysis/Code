// Height Map
// UVa ID: 13011
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 四连通BFS统计顶面连通块数（正确）
int countTopFaces(const vector<vector<int>>& h) {
    int R = (int)h.size(), C = (int)h[0].size();
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    int cnt = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) {
            if (visited[i][j]) continue;
            ++cnt;
            int v = h[i][j];
            queue<pair<int,int>> q;
            q.push({i, j});
            visited[i][j] = true;
            while (!q.empty()) {
                auto p = q.front(); q.pop();
                int r = p.first, c = p.second;
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && h[nr][nc] == v) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }
    return cnt;
}

// 统计从前往后看（前视图）的侧面数（考虑水平连通）
int countFrontFaces(const vector<vector<int>>& h) {
    int R = (int)h.size(), C = (int)h[0].size();
    int total = 0;
    // 从一列看去，某个面所在行号、面的起始高度、面的终止高度
    map<int, pair<int, int>> lastCln, currentCln;
    for (int j = 0; j < C; ++j) {
        int previous = 0;
        currentCln.clear();
        for (int i = R - 1; i >= 0; i--) {
            int now = h[i][j];
            // 高度比之前行的高度要高，会有一个暴露面
            if (previous < now) {
                // 与上一行比较，若区间不重叠则新开面，对于第一列，总是新开面
                if (!j) total++;
                // 检查上一列该行是否有可见面且与当前列的区间有重叠
                else {
                    if (!lastCln.count(i)) total++;
                    else {
                        auto [low, high] = lastCln[i];
                        if (high <= previous || now <= low) total++;
                    }
                }
                currentCln.insert({i, {previous, now}});
            }
            previous = now;
        }
        lastCln = currentCln;
    }
    return total;
}

// 顺时针旋转90度
vector<vector<int>> rotateClockwise(const vector<vector<int>>& h) {
    int R = (int)h.size(), C = (int)h[0].size();
    vector<vector<int>> rotated(C, vector<int>(R));
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            rotated[j][R - 1 - i] = h[i][j];
    return rotated;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    while (cin >> R >> C) {
        vector<vector<int>> h(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                cin >> h[i][j];

        int top = countTopFaces(h);
        int vertical = 0;
        // 四个方向：前、右、后、左（旋转三次）
        for (int k = 0; k < 4; ++k) {
            vertical += countFrontFaces(h);
            h = rotateClockwise(h);
        }
        int answer = 1 + top + vertical;
        cout << answer << '\n';
    }
    return 0;
}
