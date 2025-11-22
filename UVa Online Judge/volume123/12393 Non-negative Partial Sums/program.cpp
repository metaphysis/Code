// Non-negative Partial Sums
// UVa ID: 12393
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.210s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 10;
int n;
int a[MAXN];
long long prefixSum[MAXN];

int main() {
    while (scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            a[i + n] = a[i];
        }
        
        // 单独处理 n = 1 的情况
        if (n == 1) {
            printf("%d\n", a[0] >= 0 ? 1 : 0);
            continue;
        }
        
        int len = 2 * n;
        prefixSum[0] = a[0];
        for (int i = 1; i < len; i++)
            prefixSum[i] = prefixSum[i - 1] + a[i];
        
        deque<int> dq;
        // 初始化前 n-1 个元素
        for (int i = 0; i < n - 1; i++) {
            while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i])
                dq.pop_back();
            dq.push_back(i);
        }
        
        int count = 0;
        for (int i = n - 1; i < len - 1; i++) {
            // 维护单调队列：移除队尾比当前大的元素
            while (!dq.empty() && prefixSum[dq.back()] >= prefixSum[i])
                dq.pop_back();
            dq.push_back(i);
            
            // 移除不在窗口内的元素 [i-n+1, i]
            while (!dq.empty() && dq.front() < i - n + 1)
                dq.pop_front();
            
            // 检查移位 k = i - n + 1 是否满足条件
            // 条件：min_{j=k}^{k+n-1} prefixSum[j] >= prefixSum[k-1]
            long long base = (i - n + 1 == 0) ? 0 : prefixSum[i - n];
            if (prefixSum[dq.front()] >= base)
                count++;
        }
        printf("%d\n", count);
    }
    return 0;
}
