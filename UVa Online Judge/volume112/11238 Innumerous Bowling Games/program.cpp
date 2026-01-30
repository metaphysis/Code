// Innumerous Bowling Games
// UVa ID: 11238
// Verdict: Accepted
// Submission Date: 2026-01-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll dp[15][310][3][3];

// frame: 当前帧编号（1-10是正常帧，11处理第10帧的额外投掷）
// remain: 还需要获得的分数
// bonus1: 当前帧第一次投掷的奖励倍数
// bonus2: 当前帧第二次投掷的奖励倍数
ll dfs(int frame, int remain, int bonus1, int bonus2) {
    // 如果剩余分数为负，说明这条路径不可能达到目标分数
    if (remain < 0) return 0;
    // 所有帧都已处理完毕，检查是否恰好达到目标分数
    if (frame > 11) return remain == 0;
    // 记忆化：如果这个状态已经计算过，直接返回结果
    ll &result = dp[frame][remain][bonus1][bonus2];
    if (result != -1) return result;
    result = 0;
    if (frame <= 10) {
        // 处理非全中情况（第一次投掷击倒的瓶数first < 10）
        for (int first = 0; first < 10; ++first) {
            for (int second = 0; second <= 10; ++second) {
                // 确保两次投掷击倒的瓶数不超过10
                if (first + second < 10) {
                    // 普通帧：两次投掷后还有剩余瓶，无奖励传给下一帧
                    // 当前帧得分 = 基础分(first+second) + 奖励分(first*bonus1 + second*bonus2)
                    int score = (first + second) + first * bonus1 + second * bonus2;
                    // 下一帧没有来自当前帧的奖励
                    result += dfs(frame + 1, remain - score, 0, 0);
                } else if (first + second == 10) {
                    // 补中（spare）：第二次投掷清空所有剩余瓶
                    // 当前帧得分 = 10分 + 奖励分(first*bonus1 + second*bonus2)
                    int score = 10 + first * bonus1 + second * bonus2;
                    // 下一帧的第一次投掷将获得1倍奖励（对应bonus1=1）
                    result += dfs(frame + 1, remain - score, 1, 0);
                }
                // 注意：当first+second>10时，这种情况不会发生，所以不处理
            }
        }
        // 处理全中情况（strike）：第一次投掷就击倒所有10个瓶
        // 当前帧得分 = 10分 + 第一次投掷的奖励分(10*bonus1)
        // 注意：第二次投掷的奖励分会在下一帧作为bonus2被计算
        int strikeScore = 10 + 10 * bonus1;
        // 下一帧的两次投掷都将获得奖励：
        // bonus2 + 1: 下一帧第二次投掷的奖励倍数（累积可能存在的连续strike奖励）
        // 1: 下一帧第一次投掷的奖励倍数（因为当前帧是strike）
        result += dfs(frame + 1, remain - strikeScore, bonus2 + 1, 1);
    } else {
        // 第11帧：专门处理第10帧可能存在的额外投掷
        if (bonus1 > 0) {
            // 第10帧有额外投掷（说明第10帧是spare或strike）
            if (bonus2 == 0) {
                // spare情况：只有一次额外投掷
                for (int extra = 0; extra <= 10; ++extra) {
                    // 额外投掷的得分只计算奖励分（extra * bonus1）
                    int score = extra * bonus1;
                    result += dfs(frame + 1, remain - score, bonus2, 0);
                }
            } else {
                // strike情况：有两次额外投掷
                for (int extra1 = 0; extra1 <= 10; ++extra1) {
                    if (extra1 == 10) {
                        // 第一次额外投掷也是strike
                        for (int extra2 = 0; extra2 <= 10; ++extra2) {
                            // 得分 = 第一次额外投掷的奖励分 + 第二次额外投掷的奖励分
                            int score = 10 * bonus1 + extra2 * bonus2;
                            result += dfs(frame + 1, remain - score, 0, 0);
                        }
                    } else {
                        // 第一次额外投掷不是strike
                        for (int extra2 = 0; extra1 + extra2 <= 10; ++extra2) {
                            // 得分 = 两次额外投掷的奖励分
                            int score = extra1 * bonus1 + extra2 * bonus2;
                            result += dfs(frame + 1, remain - score, 0, 0);
                        }
                    }
                }
            }
        } else {
            // 第10帧没有额外投掷（普通帧），直接检查是否完成
            result += (remain == 0);
        }
    }
    return result;
}

int main() {
    // 初始化记忆化数组为-1，表示未计算
    memset(dp, -1, sizeof(dp));
    int score;
    // 读取每个测试用例，直到遇到-1
    while (cin >> score && score != -1) {
        // 从第1帧开始，需要获得score分，初始没有任何奖励倍数
        cout << dfs(1, score, 0, 0) << '\n';
    }
    return 0;
}
