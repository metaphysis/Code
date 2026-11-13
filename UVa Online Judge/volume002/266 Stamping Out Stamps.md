[UVa 266 Stamping Out Stamps](https://blog.csdn.net/metaphysis/article/details/161308627)

## 题目分析

题目描述了一个邮票组合问题，具体要求如下：

- 邮局最多提供 **$10$** 种不同面值的邮票。
- 每张包裹上最多只能贴 **$10$** 枚邮票。
- 给定一个需要支付的邮资金额（单位为美分），要求用邮票组合出该金额，使得：
  1. 如果能够恰好组成该金额，则选择邮票数量最少的方案；
  2. 如果无法恰好组成，则选择超出金额最小的方案；
  3. 如果仍有多种方案（相同数量、相同超出值），则选择邮票面值尽可能大的方案（即字典序最大，按降序排列邮票面值）。
- 输出时，对于每个测试数据集，先输出邮票面值（升序），然后对于每个查询金额，输出 `AMOUNT x` 和 `STAMPS USED` 后面跟所用的邮票面值（降序）。
- 如果无解（即无法用不超过 10 枚邮票组成金额或超出值），输出 `NO SOLUTION EXISTS`。

## 解题思路

### 问题建模

这是一个典型的 **有限背包 / 完全背包 + 多目标优化** 问题。与普通背包不同，我们不仅要考虑能否组成目标金额，还要考虑：

1. 最小化超出值；
2. 在超出值相同时，最小化邮票数量；
3. 在前两者相同时，最大化邮票面值的字典序（即降序排列尽可能大）。

由于每张包裹最多 $10$ 枚邮票，且面值最大不超过 $29.99$ 美分（即 $2999$ 美分），但题目中输入的面值可能较大（如 $1676543$ 美分），不过由于最多 $10$ 枚邮票，实际组成的总额不会超过 $10 \times \max(values)$。因此我们可以将搜索空间限制在一个合理的上界内。

### 算法选择

常见的解法有：
- **$\texttt{BFS}$**：以金额为状态，每次添加一枚邮票，记录使用的邮票数量和最后一步。
- **$\texttt{DP}$（动态规划）**：定义 `dp[i]` 表示组成金额 `i` 所需的最少邮票数，并记录路径。

由于金额范围可能较大（例如输入中出现了 $1676543$），但邮票数量限制为 $10$，因此实际可达的金额不会太大。我们可以设定一个搜索上界，例如 `max(values) * 10`，因为如果目标金额超过这个值，显然无法用 $10$ 枚邮票覆盖（除非面值很大，但面值也是给定的，所以这个上界是安全的）。

### 动态规划状态设计

定义：
- `coverage[i]`：组成金额 `i` 所需的最少邮票数量。初始化为一个很大的数（如 $10000$），表示不可达。
- `parent[i][0]`：组成金额 `i` 时，前一个状态的金总额（即去掉最后一枚邮票后的金额）。
- `parent[i][1]`：组成金额 `i` 时，最后一枚邮票的面值。

转移方程（完全背包，每个面值可用多次，但总邮票数不超过 $10$）：

$$
\text{如果 } i \geq values[j] \text{ 且 } coverage[i - values[j]] + 1 < coverage[i]
$$

则更新 `coverage[i]` 并记录父节点。
### 超出金额的处理

如果 `coverage[amount] > 10`，说明无法用不超过 $10$ 枚邮票恰好组成 `amount`，则从 `amount + 1` 开始向上寻找第一个能用不超过 $10$ 枚邮票组成的金额，作为新的目标金额。

### 上界的确定

代码中数组大小固定为 $3100$，这是基于面值最大约 $300$ 美分、$10$ 枚邮票最多 $3000$ 美分左右的假设。如果面值很大（如输入中的 $1676543$），则 `amount` 可能远大于 $3100$，此时代码会直接判断 `amount > values.front() * 10`（其中 `values.front()` 是最大面值）并输出 `NO SOLUTION EXISTS`。这是合理的，因为 $10$ 枚最大面值邮票都达不到 `amount`，必然无解。

### 回溯路径

从 `parent[amount][0]` 开始向前回溯，收集所有邮票面值，最后按降序输出。

## 代码实现

```cpp
// Stamping Out Stamps
// UVa ID: 266
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.140s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> values;  // 存储邮票面值
int n;               // 邮票种类数

// 将给定金额转换为邮票组合
void convert(int amount)
{
    // coverage[i] 表示组成金额 i 所需的最少邮票数
    // parent[i][0] 表示组成金额 i 的前一个金额
    // parent[i][1] 表示组成金额 i 时使用的最后一枚邮票面值
    int coverage[3100], parent[3100][2];
    
    // 初始化
    for (int i = 0; i < 3100; i++)
    {
        coverage[i] = 10000;  // 初始化为一个大数，表示不可达
        parent[i][0] = -1;
        parent[i][1] = -1;
    }
    
    coverage[0] = 0;  // 金额 0 不需要邮票
    
    // 完全背包 DP，金额从 1 到 3099
    for (int i = 1; i < 3100; i++)
        for (int j = 0; j < n; j++)
        {
            // 如果当前金额 i 可以减去一个邮票面值，且新方案邮票数更少
            if (i >= values[j] && (coverage[i - values[j]] + 1) < coverage[i])
            {
                coverage[i] = coverage[i - values[j]] + 1;
                parent[i][0] = i - values[j];
                parent[i][1] = values[j];
            }
        }
    
    // 如果无法用不超过 10 枚邮票恰好组成 amount，则寻找超出 amount 的最小金额
    if (coverage[amount] > 10)
    {
        for (int i = amount + 1; i < 3100; i++)
            if (coverage[i] <= 10)
            {
                amount = i;
                break;
            }
    }
    
    // 回溯路径，收集使用的邮票
    vector<int> stamps;
    int end = parent[amount][0];
    stamps.push_back(parent[amount][1]);
    while (parent[end][0] != -1)
    {
        stamps.push_back(parent[end][1]);
        end = parent[end][0];
    }
    
    // 按降序输出邮票面值
    sort(stamps.begin(), stamps.end(), greater<int>());
    cout << "STAMPS USED";
    for (int i = 0; i < stamps.size(); i++)
        cout << " " << stamps[i];
    cout << endl;
}

int main(int argc, char *argv[])
{
    while (cin >> n, n > 0)
    {
        values.resize(n);
        for (int i = 1; i <= n; i++)
            cin >> values[i - 1];
        
        // 输出邮票面值（升序）
        sort(values.begin(), values.end());
        cout << "STAMP VALUES";
        for (int i = 0; i < values.size(); i++)
            cout << " " << values[i];
        cout << endl << endl;
        
        // 将面值反转为降序，以便 DP 时优先考虑大面值
        reverse(values.begin(), values.end());
        
        int amount;
        while (cin >> amount, amount > 0)
        {
            cout << "AMOUNT " << amount << endl;
            
            // 如果最大面值的 10 倍仍小于 amount，则无解
            if (amount > values.front() * 10)
                cout << "NO SOLUTION EXISTS" << endl;
            else
                convert(amount);
            
            cout << endl;
        }
    }
    
    return 0;
}
```

## 总结

本题的核心是 **有限制数量的完全背包 + 多目标优化**。通过动态规划记录最少邮票数，并处理超出金额的情况，最后回溯输出邮票序列。需要注意输出格式，每个数据集之间有空行，金额和邮票列表也要按格式输出。
