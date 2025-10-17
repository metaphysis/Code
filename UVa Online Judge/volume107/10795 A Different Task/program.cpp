// A Different Task
// UVa ID: 10795
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 递归函数：将P状态中最大的n个盘子全部移动到target柱子所需的最小步数
ll solve(const vector<int>& P, int n, int target) {
    if (n == 0) return 0;  // 没有盘子需要移动
    if (P[n] == target) {
        // 当前盘子已经在目标柱子上，只需处理上面的n-1个盘子
        return solve(P, n - 1, target);
    } else {
        // 计算第三根柱子（既不是当前所在也不是目标柱子）
        int other = 6 - P[n] - target;
        // 先把上面的n-1个盘子移到other柱子，然后移动当前盘子
        // 移动n-1个盘子需要2^(n-1)-1步，加上移动当前盘子的1步
        return solve(P, n - 1, other) + (1LL << (n - 1));
    }
}

int main() {
    int N, caseNum = 1;
    while (cin >> N && N != 0) {
        vector<int> start(N + 1), target(N + 1);
        // 读入初始状态，start[i]表示第i个盘子的初始位置
        for (int i = 1; i <= N; i++) cin >> start[i];
        // 读入目标状态，target[i]表示第i个盘子的目标位置
        for (int i = 1; i <= N; i++) cin >> target[i];
        
        // 从最大的盘子开始找，找到第一个需要移动的盘子
        int k = N;
        while (k >= 1 && start[k] == target[k]) k--;
        
        ll ans = 0;
        if (k >= 1) {
            // 计算第三根柱子
            int other = 6 - start[k] - target[k];
            // 计算总步数
            ans = solve(start, k - 1, other) + 1 + solve(target, k - 1, other);
        }
        cout << "Case " << caseNum++ << ": " << ans << endl;
    }
    return 0;
}
