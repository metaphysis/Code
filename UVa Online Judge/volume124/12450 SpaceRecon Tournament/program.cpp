// SpaceRecon Tournament
// UVa ID: 12450
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Player {
    string handle;
    int wins;
    int roundSurvived;      // 晋级轮数 k
};

// 计算给定胜场 wins 在总轮数 M、前 R 轮为 BO3 的情况下，玩家晋级的轮数 k
int getRound(int wins, int M, int R) {
    for (int k = 0; k <= M; ++k) {
        int minW = 2 * min(k, R) + 3 * max(0, k - R);   // 晋级 k 轮至少需要的胜场
        int maxW;
        if (k == M) {
            maxW = minW;                                // 冠军没有淘汰轮，胜场固定
        } else {
            int nextRound = k + 1;                      // 被淘汰的轮次
            int maxExtra = (nextRound <= R) ? 1 : 2;    // BO3 最多赢 1 局，BO5 最多赢 2 局
            maxW = minW + maxExtra;
        }
        if (wins >= minW && wins <= maxW) return k;
    }
    return -1;  // 无法匹配
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        int M;
        cin >> M;
        int total = 1 << M;
        vector<Player> players(total);
        for (int i = 0; i < total; ++i) {
            cin >> players[i].handle >> players[i].wins;
        }

        int validR = -1;
        vector<int> rounds(total);

        // 枚举 R
        for (int R = 0; R <= M; ++R) {
            vector<int> cnt(M + 1, 0);
            bool ok = true;
            vector<int> curRounds(total);

            for (int i = 0; i < total; ++i) {
                int k = getRound(players[i].wins, M, R);
                if (k == -1) { ok = false; break; }
                curRounds[i] = k;
                cnt[k]++;
            }
            if (!ok) continue;

            // 检查频数是否符合淘汰赛结构
            for (int k = 0; k < M; ++k) {
                if (cnt[k] != (1 << (M - 1 - k))) { ok = false; break; }
            }
            if (ok && cnt[M] == 1) {
                validR = R;
                rounds = curRounds;
                break;
            }
        }

        // 将计算结果赋给玩家
        for (int i = 0; i < total; ++i) players[i].roundSurvived = rounds[i];

        // 排序：先按晋级轮数降序，再按昵称字典序升序
        sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            if (a.roundSurvived != b.roundSurvived) return a.roundSurvived > b.roundSurvived;
            return a.handle < b.handle;
        });

        // 输出
        for (const auto& p : players) cout << p.handle << '\n';
    }

    return 0;
}
