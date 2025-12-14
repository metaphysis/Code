// Cat
// UVa ID: 10715
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.830s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n, n != 0) {
        vector<double> weights(n);
        double minWeight = 1000.0;  // 初始化一个较大的值，用于记录最小重量
        double totalWeight = 0.0;

        // 读入重量并计算总重量和最小重量
        for (int i = 0; i < n; ++i) {
            cin >> weights[i];
            totalWeight += weights[i];
            if (weights[i] < minWeight) minWeight = weights[i];
        }

        // 动态计算放大倍数，确保最小重量放大后至少为 1000
        double scale = ceil(1000.0 / minWeight);
        
        // 将重量转换为整数
        vector<int> intWeights(n);
        for (int i = 0; i < n; ++i) {
            intWeights[i] = int(round(weights[i] * scale));
        }

        int totalInt = round(totalWeight * scale);
        int targetInt = totalInt / 2;
        int allowedDiffInt = round(totalWeight * scale * 0.02);  // 2% 误差对应的整数值

        // 动态规划：dp[sum] 表示是否存在子集和为 sum，prev[sum] 记录最后一块石头编号
        vector<bool> dp(totalInt + 1, false);
        vector<int> prev(totalInt + 1, 0);
        dp[0] = true;

        // 0/1背包动态规划
        for (int i = 0; i < n; ++i) {
            for (int s = totalInt - intWeights[i]; s >= 0; --s) {
                if (dp[s] && !dp[s + intWeights[i]]) {
                    dp[s + intWeights[i]] = true;
                    prev[s + intWeights[i]] = i + 1;  // 记录石头编号（1-based）
                }
            }
        }

        // 寻找最接近 targetInt 且误差在允许范围内的子集和
        int bestSum = 0;
        for (int s = targetInt; s <= totalInt; ++s) {
            if (dp[s] && abs(s - targetInt) <= allowedDiffInt) {
                bestSum = s;
                break;
            }
        }
        if (bestSum == 0) {
            for (int s = targetInt; s >= 0; --s) {
                if (dp[s] && abs(s - targetInt) <= allowedDiffInt) {
                    bestSum = s;
                    break;
                }
            }
        }

        // 回溯得到右舷石头编号
        vector<int> result;
        int cur = bestSum;
        while (cur > 0) {
            int rockId = prev[cur];
            result.push_back(rockId);
            cur -= intWeights[rockId - 1];  // 重量数组索引是 0-based
        }

        // 输出结果（按升序排序）
        sort(result.begin(), result.end());
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
