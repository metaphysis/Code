// Fixing the Great Wall
// UVa ID: 1336
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1005;
const double INF = 1e18;

struct Section {
    int position;
    int baseCost;
    int deltaCost;
    bool operator<(const Section& other) const {
        return position < other.position;
    }
} sections[MAX_N];

int numSections, robotSpeed, startPosition;
double dpLeft[MAX_N][MAX_N], dpRight[MAX_N][MAX_N];
int prefixSumDelta[MAX_N];

// 获取区间 [l, r] 之外的 delta 成本之和
int getRemainingDeltaSum(int left, int right) {
    return prefixSumDelta[numSections] - (prefixSumDelta[right] - prefixSumDelta[left - 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> numSections >> robotSpeed >> startPosition) {
        if (numSections == 0 && robotSpeed == 0 && startPosition == 0) break;

        // 读取损坏区段数据
        for (int i = 1; i <= numSections; i++) {
            cin >> sections[i].position >> sections[i].baseCost >> sections[i].deltaCost;
        }

        // 添加虚拟起点（机器人初始位置）
        numSections++;
        sections[numSections].position = startPosition;
        sections[numSections].baseCost = 0;
        sections[numSections].deltaCost = 0;

        // 按位置排序
        sort(sections + 1, sections + numSections + 1);

        // 计算 delta 成本的前缀和
        prefixSumDelta[0] = 0;
        for (int i = 1; i <= numSections; i++) {
            prefixSumDelta[i] = prefixSumDelta[i - 1] + sections[i].deltaCost;
        }

        // 找到机器人初始位置对应的索引
        int startIndex = -1;
        for (int i = 1; i <= numSections; i++) {
            if (sections[i].position == startPosition && 
                sections[i].baseCost == 0 && 
                sections[i].deltaCost == 0) {
                startIndex = i;
                break;
            }
        }

        // 初始化 DP 数组
        for (int i = 1; i <= numSections; i++) {
            for (int j = i; j <= numSections; j++) {
                dpLeft[i][j] = dpRight[i][j] = INF;
            }
        }
        dpLeft[startIndex][startIndex] = dpRight[startIndex][startIndex] = 0;

        // 区间动态规划
        for (int length = 2; length <= numSections; length++) {
            for (int i = 1; i + length - 1 <= numSections; i++) {
                int j = i + length - 1;

                // 从左边扩展：最后停在左端点 i
                double costFromLeft = dpLeft[i + 1][j] + 
                    (sections[i + 1].position - sections[i].position) * 1.0 / robotSpeed * 
                    getRemainingDeltaSum(i + 1, j);
                double costFromRight = dpRight[i + 1][j] + 
                    (sections[j].position - sections[i].position) * 1.0 / robotSpeed * 
                    getRemainingDeltaSum(i + 1, j);
                dpLeft[i][j] = min(costFromLeft, costFromRight) + sections[i].baseCost;

                // 从右边扩展：最后停在右端点 j
                costFromRight = dpRight[i][j - 1] + 
                    (sections[j].position - sections[j - 1].position) * 1.0 / robotSpeed * 
                    getRemainingDeltaSum(i, j - 1);
                costFromLeft = dpLeft[i][j - 1] + 
                    (sections[j].position - sections[i].position) * 1.0 / robotSpeed * 
                    getRemainingDeltaSum(i, j - 1);
                dpRight[i][j] = min(costFromRight, costFromLeft) + sections[j].baseCost;
            }
        }

        // 输出结果（向下取整）
        long long result = (long long)floor(min(dpLeft[1][numSections], dpRight[1][numSections]));
        cout << result << "\n";

        // 恢复 numSections 的原始值
        numSections--;
    }

    return 0;
}
