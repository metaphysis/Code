// Splat Inc
// UVa ID: 10873
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> stacks;   // 每列从底到顶存储球ID
vector<int> ballColor;        // ID -> 颜色 (0红,1绿,2蓝)
int totalBalls;

// 处理所有可能的崩塌，直至稳定
void collapseAll() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int c = 0; c < n; ++c) {
            int h = (int)stacks[c].size();
            bool leftOk = (c > 0 && h - (int)stacks[c-1].size() >= 3);
            bool rightOk = (c < n-1 && h - (int)stacks[c+1].size() >= 3);
            if (!leftOk && !rightOk) continue;

            changed = true;
            if (leftOk && rightOk) {          // 两侧都满足，移动顶部和次顶部
                int topId = stacks[c].back();
                stacks[c].pop_back();
                int secondId = stacks[c].back();
                stacks[c].pop_back();
                stacks[c-1].push_back(topId);
                stacks[c+1].push_back(secondId);
            } else if (leftOk) {              // 仅左侧满足，移动顶部
                int topId = stacks[c].back();
                stacks[c].pop_back();
                stacks[c-1].push_back(topId);
            } else {                          // 仅右侧满足，移动顶部
                int topId = stacks[c].back();
                stacks[c].pop_back();
                stacks[c+1].push_back(topId);
            }
            break;   // 重新扫描
        }
    }
}

// 滴落一个颜色为 color 的球到列 col，返回球ID
int dropBall(int col, int color) {
    int id = (int)ballColor.size();
    ballColor.push_back(color);
    stacks[col].push_back(id);
    ++totalBalls;
    collapseAll();
    return id;
}

// 查找球 id 所在列和高度（从1开始）
pair<int,int> findBall(int id) {
    for (int c = 0; c < n; ++c)
        for (int i = 0; i < (int)stacks[c].size(); ++i)
            if (stacks[c][i] == id)
                return {c, i + 1};
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 1;
    while (true) {
        int rInt, gInt, bInt, rCol, gCol, bCol;
        cin >> n >> m >> rInt >> gInt >> bInt >> rCol >> gCol >> bCol;
        if (n == 0 && m == 0 && rInt == 0 && gInt == 0 && bInt == 0 &&
            rCol == 0 && gCol == 0 && bCol == 0) break;

        stacks.assign(n, vector<int>());
        ballColor.clear();
        totalBalls = 0;

        struct Feeder { bool active; int interval; int col; int nextTime; };
        vector<Feeder> feeders(3);
        feeders[0] = {rInt > 0, rInt, rCol, rInt > 0 ? 1 : 0};
        feeders[1] = {gInt > 0, gInt, gCol, gInt > 0 ? 1 : 0};
        feeders[2] = {bInt > 0, bInt, bCol, bInt > 0 ? 1 : 0};

        while (true) {
            if (totalBalls == n * m) break;

            int minTime = INT_MAX;
            bool anyActive = false;
            for (int i = 0; i < 3; ++i)
                if (feeders[i].active) {
                    anyActive = true;
                    minTime = min(minTime, feeders[i].nextTime);
                }
            if (!anyActive) break;

            // 同一时刻按红→绿→蓝顺序处理
            for (int color = 0; color < 3; ++color) {
                if (!feeders[color].active || feeders[color].nextTime != minTime)
                    continue;

                int id = dropBall(feeders[color].col, color);
                auto pos = findBall(id);
                int height = pos.second;

                if (height == m)
                    feeders[color].active = false;
                else
                    feeders[color].nextTime += feeders[color].interval;
            }
        }

        vector<int> cnt(3, 0);
        for (int c = 0; c < n; ++c)
            for (int id : stacks[c])
                ++cnt[ballColor[id]];

        int empty = n * m - totalBalls;
        cout << "Case " << caseNo << ": "
             << cnt[0] << " " << cnt[1] << " " << cnt[2] << " " << empty << "\n";
        ++caseNo;
    }
    return 0;
}
