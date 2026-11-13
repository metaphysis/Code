[UVa 231 Testing the CATCHER](https://blog.csdn.net/metaphysis/article/details/161207581)

## 问题分析

本题是典型的**最长非递增子序列**（$\texttt{Longest Non-Increasing Subsequence}$）问题。题目描述了一个导弹拦截系统 $\texttt{CATCHER}$，它能够拦截后续导弹的条件是：后续导弹的高度**不高于**上一次拦截的导弹高度。由于导弹按照时间顺序依次到来，我们需要在给定的高度序列中找出最长的非递增子序列的长度。

需要注意的是，题目中的输入是以 `-1` 作为每个测试用例的结束标志，而连续两个 `-1` 则表示输入结束。

## 解题思路

求解最长非递增子序列的长度，有多种方法：

1. **动态规划法**：定义 $dp[i]$ 表示以第 $i$ 个导弹结尾的最长非递增子序列的长度，状态转移方程为：

   $$dp[i] = \max(dp[j]) + 1, \quad \text{其中 } j < i \text{ 且 } heights[j] \ge heights[i]$$

   时间复杂度为 $O(n^2)$，$n$ 为导弹数量。

2. **二分查找优化法**（本题代码采用的方法）：  
   由于我们只关心最长序列的长度，可以使用一个数组 `m` 来维护当前最长非递增子序列的“尾部元素”。对于非递增子序列，当遇到一个新元素时，我们使用 `upper_bound` 找到第一个**大于**当前元素的位置（因为我们要保持非递增，所以新元素应该替换掉第一个比它大的元素），然后进行替换。最后 `m` 的长度即为答案。

   需要注意的是，在计算之前，代码先将原序列反转，然后使用 `upper_bound` 处理，这实际上是在求解**最长非递减子序列**，等价于原问题的最长非递增子序列。

## 代码实现

```cpp
// Testing the CATCHER
// UVa ID: 231
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> heights;

// 计算最长非递增子序列的长度
int lis() {
    // 反转序列，将非递增问题转换为非递减问题
    reverse(heights.begin(), heights.end());
    
    // m 维护当前最长非递减子序列的尾部元素
    vector<int> m;
    m.push_back(heights.front());
    
    for (int i = 1; i < heights.size(); i++)
        // 如果当前高度不小于尾部元素，直接扩展
        if (heights[i] >= m.back())
            m.push_back(heights[i]);
        else
        {
            // 找到第一个大于 heights[i] 的位置并替换
            int n = upper_bound(m.begin(), m.end(), heights[i]) - m.begin();
            m[n] = heights[i];
        }
    
    return m.size();
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    bool first = true;
    int height, cases = 0;
    
    // 读取每个测试用例，以 -1 结束
    while (cin >> height, height != -1)
    {
        heights.clear();
        heights.push_back(height);
        
        // 读取同一测试用例的后续高度
        while (cin >> height, height != -1)
            heights.push_back(height);
        
        // 输出空行分隔不同测试用例
        if (first)
            first = false;
        else
            cout << endl;
        
        cases++;
        cout << "Test #" << cases << ":" << endl;
        cout << "  maximum possible interceptions: " << lis() << endl;
    }
    
    return 0;
}
```

## 总结

本题本质上是一个经典的**最长非递增子序列**问题，使用 $O(n \log n)$ 的二分查找优化方法可以在规定时间内完成计算。理解问题转化为最长非递增子序列是关键，代码实现相对简单。
