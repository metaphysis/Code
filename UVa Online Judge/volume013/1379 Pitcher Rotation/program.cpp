// Pitcher Rotation
// UVa ID: 1379
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.630s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const int MAXG = 250;
const int MAXK = 15;  // 候选投手最大数量，实际上由于在线测试数据较弱，设置为 6 也可以通过，运行时间更短

int n, m, g, days;
int win[MAXN][MAXN];
int schedule[MAXG];
int best[MAXN][MAXK];
int dp[2][MAXK][MAXK][MAXK][MAXK];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &g);
        days = g + 10;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &win[i][j]);

        for (int i = 1; i <= days; i++)
            scanf("%d", &schedule[i]);

        // 预处理每个对手的前 MAXK-1 名投手
        for (int i = 1; i <= m; i++) {
            pair<int, int> pitchers[MAXN];
            for (int j = 1; j <= n; j++)
                pitchers[j] = make_pair(win[i][j], j);
            sort(pitchers + 1, pitchers + n + 1,
                 [](const pair<int, int>& a, const pair<int, int>& b) {
                     return a.first > b.first;
                 });
            int cnt = 0;
            for (int k = 1; k <= n && cnt < MAXK - 1; k++)
                best[i][++cnt] = pitchers[k].second;
            for (int k = cnt + 1; k < MAXK; k++)
                best[i][k] = 0;
        }

        memset(dp, -1, sizeof(dp));
        dp[0][0][0][0][0] = 0;

        int cur = 0, pre = 1;
        int ans = 0;

        for (int day = 1; day <= days; day++) {
            cur ^= 1;
            pre ^= 1;
            memset(dp[cur], -1, sizeof(dp[cur]));

            int team = schedule[day];

            for (int a = 0; a < MAXK; a++) {
                for (int b = 0; b < MAXK; b++) {
                    for (int c = 0; c < MAXK; c++) {
                        for (int d = 0; d < MAXK; d++) {
                            int last_val = dp[pre][a][b][c][d];
                            if (last_val == -1) continue;

                            if (team == 0) {
                                // 没有比赛，状态平移
                                int& target = dp[cur][b][c][d][0];
                                if (last_val > target) target = last_val;
                                if (last_val > ans) ans = last_val;
                            } else {
                                // 有比赛，尝试所有候选投手
                                for (int k = 1; k < MAXK; k++) {
                                    int pitcher = best[team][k];
                                    if (pitcher == 0) continue;

                                    bool conflict = false;
                                    if (day - 4 >= 1 && schedule[day - 4] != 0 && best[schedule[day - 4]][a] == pitcher) conflict = true;
                                    if (!conflict && day - 3 >= 1 && schedule[day - 3] != 0 && best[schedule[day - 3]][b] == pitcher) conflict = true;
                                    if (!conflict && day - 2 >= 1 && schedule[day - 2] != 0 && best[schedule[day - 2]][c] == pitcher) conflict = true;
                                    if (!conflict && day - 1 >= 1 && schedule[day - 1] != 0 && best[schedule[day - 1]][d] == pitcher) conflict = true;

                                    if (conflict) continue;

                                    int val = last_val + win[team][pitcher];
                                    int& target = dp[cur][b][c][d][k];
                                    if (val > target) target = val;
                                    if (val > ans) ans = val;
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("%d.%02d\n", ans / 100, ans % 100);
    }
    return 0;
}
