// Tile Puzzle
// UVa ID: 798
// Verdict: Accepted
// Submission Date: 2026-07-04
// UVa Run Time: 0.930s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Group {
    int m;                // 剩余数量
    int w, h;             // 原始宽高
    int dirCnt;           // 有效方向数（1 或 2）
    int dirs[2][2];       // 每个方向的宽、高
};

int W, H, N;
vector<Group> groups;
bool used[100][100];
unsigned long long ans;

void dfs() {
    // 找第一个空白格
    int x = -1, y = -1;
    for (int i = 0; i < H && x == -1; ++i)
        for (int j = 0; j < W; ++j)
            if (!used[i][j]) { x = j; y = i; break; }

    if (x == -1) { ++ans; return; }

    for (size_t idx = 0; idx < groups.size(); ++idx) {
        Group &g = groups[idx];
        if (g.m == 0) continue;

        for (int d = 0; d < g.dirCnt; ++d) {
            int ww = g.dirs[d][0], hh = g.dirs[d][1];
            if (x + ww > W || y + hh > H) continue;

            bool ok = true;
            for (int r = y; r < y + hh && ok; ++r)
                for (int c = x; c < x + ww && ok; ++c)
                    if (used[r][c]) ok = false;

            if (!ok) continue;

            // 放置
            for (int r = y; r < y + hh; ++r)
                for (int c = x; c < x + ww; ++c)
                    used[r][c] = true;
            --g.m;

            dfs();

            // 回溯
            ++g.m;
            for (int r = y; r < y + hh; ++r)
                for (int c = x; c < x + ww; ++c)
                    used[r][c] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> W >> H >> N) {
        groups.clear();
        for (int i = 0; i < N; ++i) {
            int m, w, h;
            cin >> m >> w >> h;
            Group g;
            g.m = m;
            g.w = w; g.h = h;
            g.dirCnt = 0;
            // 原始方向
            g.dirs[g.dirCnt][0] = w; g.dirs[g.dirCnt][1] = h; ++g.dirCnt;
            // 若宽高不等，增加旋转方向
            if (w != h) {
                g.dirs[g.dirCnt][0] = h; g.dirs[g.dirCnt][1] = w; ++g.dirCnt;
            }
            groups.push_back(g);
        }

        // 按面积从大到小排序，加速搜索
        sort(groups.begin(), groups.end(), [](const Group &a, const Group &b) {
            return a.w * a.h > b.w * b.h;
        });

        // 清空棋盘
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                used[i][j] = false;

        ans = 0;
        dfs();
        cout << ans << '\n';
    }

    return 0;
}
