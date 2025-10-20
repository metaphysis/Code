// Beijing Guards
// UVa ID: 1335
// Verdict: Accepted
// Submission Date: 2025-10-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 200010;

int awardsNeeded[MAX];    // 每个守卫需要的奖章数量
int sameAwards[MAX];      // sameAwards[i]: 第 i 个守卫使用与第 1 个守卫相同的奖章数量
int diffAwards[MAX];      // diffAwards[i]: 第 i 个守卫使用与第 1 个守卫不同的奖章数量
int guardCount;

// 检查奖章总数 totalAwards 是否足够分配给所有守卫
bool canAssignAwards(int totalAwards) {
    // samePool: 与第一个守卫相同的奖章池大小（等于第一个守卫需要的奖章数）
    // diffPool: 与第一个守卫不同的奖章池大小
    int samePool = awardsNeeded[1];
    int diffPool = totalAwards - awardsNeeded[1];
    // 初始化第一个守卫：全部使用"相同"奖章
    sameAwards[1] = awardsNeeded[1];
    diffAwards[1] = 0;
    // 为第 2 到第 guardCount 个守卫分配奖章
    for(int i = 2; i <= guardCount; i++) {
        if(i % 2 == 1) { 
            // 奇数下标的守卫：尽量多用"不同"奖章
            // 可用的不同奖章数 = 不同奖章池总数 - 前一个守卫使用的不同奖章数
            diffAwards[i] = min(diffPool - diffAwards[i-1], awardsNeeded[i]);
            sameAwards[i] = awardsNeeded[i] - diffAwards[i];
        }
        else { 
            // 偶数下标的守卫：尽量多用"相同"奖章  
            // 可用的相同奖章数 = 相同奖章池总数 - 前一个守卫使用的相同奖章数
            sameAwards[i] = min(samePool - sameAwards[i-1], awardsNeeded[i]);
            diffAwards[i] = awardsNeeded[i] - sameAwards[i];
        }
    }
    // 关键检查：第 guardCount 个守卫与第 1 个守卫相邻，不能有相同奖章
    // 所以 sameAwards[guardCount] 必须为 0（最后一个守卫不能使用任何与第 1 个守卫相同的奖章）
    return sameAwards[guardCount] == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin >> guardCount) {
        if(guardCount == 0) break;
        int maxAdjacentSum = 0;  // 相邻守卫需求之和的最大值
        // 读入数据并计算相邻需求之和的最大值
        for(int i = 1; i <= guardCount; i++) {
            cin >> awardsNeeded[i];
            // 计算当前守卫与前一个守卫的需求之和
            if(i > 1) {
                maxAdjacentSum = max(maxAdjacentSum, awardsNeeded[i] + awardsNeeded[i-1]);
            }
        }
        // 检查首尾两个守卫的需求之和（环形）
        maxAdjacentSum = max(maxAdjacentSum, awardsNeeded[1] + awardsNeeded[guardCount]);
        // 特殊情况处理
        if(guardCount == 1) {
            // 只有一个守卫，直接输出其需求
            cout << awardsNeeded[1] << endl;
            continue;
        }
        else if(guardCount % 2 == 0) {
            // 偶数个守卫：答案就是相邻需求之和的最大值
            // 因为可以将守卫分成两组交替分配奖章
            cout << maxAdjacentSum << endl;
            continue;
        }
        // 奇数个守卫：使用二分查找确定最小奖章数
        int low = maxAdjacentSum;      // 下界：相邻需求之和的最大值
        int high = INF;                // 上界：一个足够大的数
        // 二分查找
        while(low < high) {
            int mid = (low + high) / 2;
            if(canAssignAwards(mid)) {
                // mid 足够，尝试更小的值
                high = mid;
            }
            else {
                // mid 不够，需要更大的值
                low = mid + 1;
            }
        }
        // 输出最小奖章数
        cout << low << endl;
    }
    return 0;
}
