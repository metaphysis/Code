[UVa 323 Jury Compromise](https://blog.csdn.net/metaphysis/article/details/161512540)

## 题目描述

在 $\texttt{Frohnia}$ 这个遥远的国度，法庭审判的裁决由从普通公众中选出的陪审团决定。每次审判开始前，需要选择陪审团，具体步骤如下：首先从公众中随机抽取若干人。对于这个候选池中的每个人，控辩双方都会给出一个 $0$ 到 $20$ 的评分，表示对该人的偏好程度。$0$ 表示完全不喜，$20$ 表示该人被认为是陪审团的理想人选。

基于双方的评分，法官选择陪审团。为了确保公平，陪审团偏向辩护方或控诉方的倾向应尽可能平衡。因此，陪审团的选择必须令双方都满意。

现给出 $n$ 个候选人的控方评分 $p_i$ 和辩方评分 $d_i$，需要从中选择 $m$ 人组成陪审团。设 $\mathcal{I}$ 是大小为 $m$ 的子集，定义：

- $D(\mathcal{I}) = \sum_{k \in \mathcal{I}} d_k$（辩方总分）
- $P(\mathcal{I}) = \sum_{k \in \mathcal{I}} p_k$（控方总分）

最优陪审团应满足：
1. 首先使 $|D(\mathcal{I}) - P(\mathcal{I})|$ 最小
2. 如果有多个陪审团满足条件，选择 $D(\mathcal{I}) + P(\mathcal{I})$ 最大的那个

要求：编写程序实现这一陪审团选择过程。

### 输入格式

输入文件包含多个陪审团选择轮次。每个轮次以一行两个整数 $n$ 和 $m$ 开始：
- $n$：候选人数量（$1 \leq n \leq 200$）
- $m$：陪审团人数（$1 \leq m \leq 20$，且 $m \leq n$）

接下来 $n$ 行，每行两个整数 $p_i$ 和 $d_i$。每个轮次后有一个空行。

文件以 $n = m = 0$ 的轮次结束。

### 输出格式

对于每个轮次，输出一行 `Jury #1`、`Jury #2` 等。

下一行输出 `Best jury has value X for prosecution and value Y for defence:`，其中 $X = P(\mathcal{I})$，$Y = D(\mathcal{I})$。

再下一行输出选中的 $m$ 个候选人的编号（按升序排列），每个编号前有一个空格。

每个测试用例后输出一个空行。

### 样例输入

```
4 2

1 2
2 3
4 1
6 2

0 0
```

### 样例输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3
```

---

## 题目分析

### 问题的本质

这是一个**二维约束的组合优化问题**。我们需要从 $n$ 个物品（候选人）中选取 $m$ 个，使得：
- 目标 $1$：最小化 $|P - D|$（控辩差）
- 目标 $2$：最大化 $P + D$（总分）

这是一个典型的**多目标背包问题**（$\texttt{multiple-objective knapsack}$），可以用动态规划解决。

### 关键观察

设第 $i$ 个候选人的差值为 $diff_i = p_i - d_i$，和为 $sum_i = p_i + d_i$。

选择 $m$ 个人的总差值：
$$
total\_diff = \sum_{j=1}^{m} diff_{i_j}
$$

总总分：
$$
total\_sum = \sum_{j=1}^{m} sum_{i_j}
$$

我们的目标：
$1$. 最小化 $|total\_diff|$
$2$. 在差值相同的情况下，最大化 $total\_sum$

### 差值范围

$p_i$ 和 $d_i$ 都在 $0 \sim 20$ 之间，因此：
- 单个差值的范围：$-20 \sim 20$
- $m$ 个人的总差值范围：$-20m \sim 20m$

对于 $m \leq 20$，差值范围约为 $[-400, 400]$。这个范围是可管理的。

### 动态规划状态定义

定义 $dp[j][k]$ = 选择 $j$ 个人，总差值为 $k$ 时，能达到的最大总分数 $total\_sum$。

其中 $k$ 是差值，需要进行坐标偏移（$\texttt{offset}$）处理，因为数组索引不能为负。

设 $offset = 20 \times m$，则实际差值 $k$ 对应索引 $k + offset$。

### 状态转移

考虑第 $i$ 个人，我们决定是否选择他：

如果不选，状态不变。

如果选，则从 $j-1$ 个人、差值 $k' = k - diff_i$ 的状态转移过来：
$$
dp[j][k + offset] = \max(dp[j][k + offset],\ dp[j-1][k' + offset] + sum_i)
$$

其中 $k' = k - diff_i$。

### 记录路径

由于需要输出选中的候选人编号，每个状态还需要记录达到该状态时选择了哪些人。由于 $n \leq 200$，$m \leq 20$，可以使用 `vector<int>` 记录路径。

### 最终答案

在 $dp[m][k]$ 中，找到使 $|k|$ 最小的 $k$。如果多个 $k$ 满足，选择总分最大的那个。

---
## 参考代码

```cpp
// Jury Compromise
// UVa ID: 323
// Verdict: Accepted
// Submission Date: 2018-09-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 候选人结构体
struct person
{
    int prosecution, defence, sum, diff;
};

// DP 状态结构体
struct data
{
    int sum;                    // 当前状态的最大总分
    int pre_diff;               // 前驱状态的差值（用于调试）
    vector<int> selected;       // 选中的候选人编号列表
};

int n, m, cases = 0, offset;
person jury[210];
data cache[21][810];  // cache[j][k]: 选 j 人，差值为 k-offset 的最大总分

void knapsack()
{
    // 差值范围：[-offset, offset] 经过偏移后为 [0, 2*offset]
    int top = 2 * offset * m;
    
    // 初始化 DP 数组
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= top; j++)
        {
            cache[i][j].sum = -1;
            cache[i][j].selected.clear();
        }
    cache[0][0].sum = 0;  // 基础状态：选 0 人，差值 0，总分 0

    // 动态规划：0-1 背包
    for (int i = 1; i <= n; i++)                    // 枚举每个人
        for (int j = min(i, m); j >= 1; j--)        // 枚举已选人数（逆序）
            for (int k = (jury[i].diff + offset); k <= top; k++)  // 枚举当前差值
            {
                int pre_diff = k - (jury[i].diff + offset);
                if (cache[j - 1][pre_diff].sum != -1)
                {
                    int next = cache[j - 1][pre_diff].sum + jury[i].sum;
                    if (next > cache[j][k].sum)
                    {
                        cache[j][k].sum = next;
                        cache[j][k].selected = cache[j - 1][pre_diff].selected;
                        cache[j][k].selected.push_back(i);
                        cache[j][k].pre_diff = pre_diff;
                    }
                }
            }

    cout << "Jury #" << ++cases << '\n';
    
    // 寻找最优解：从差值 0 向两边扩展
    int last_diff = offset * m;  // 对应差值 0 的索引
    for (int i = 0; ; i++)
    {
        int j = last_diff - i, k = last_diff + i;
        if (cache[m][j].sum == -1 && cache[m][k].sum == -1) 
            continue;
        
        if (cache[m][j].sum != -1 && cache[m][k].sum != -1)
        {
            // 两个方向都可达，选择总分较大的
            if (cache[m][j].sum > cache[m][k].sum)
                last_diff = j;
            else
                last_diff = k;
        }
        else if (cache[m][j].sum != -1)
        {
            last_diff = j;
        }
        else
        {
            last_diff = k;
        }
        break;
    }

    // 计算控方和辩方总分
    int sum_of_prosecution = 0, sum_of_defence = 0;
    sort(cache[m][last_diff].selected.begin(), cache[m][last_diff].selected.end());
    for (auto k : cache[m][last_diff].selected)
    {
        sum_of_prosecution += jury[k].prosecution;
        sum_of_defence += jury[k].defence;
    }
    
    // 输出结果
    cout << "Best jury has value " << sum_of_prosecution;
    cout << " for prosecution and value " << sum_of_defence;
    cout << " for defence:\n";
    for (auto k : cache[m][last_diff].selected)
        cout << ' ' << k;
    cout << "\n\n";
}

int main(int argc, char *argv[])
{
    while (cin >> n >> m, n > 0)
    {
        offset = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> jury[i].prosecution >> jury[i].defence;
            jury[i].sum = jury[i].prosecution + jury[i].defence;
            jury[i].diff = jury[i].prosecution - jury[i].defence;
            offset = max(offset, max(jury[i].prosecution, jury[i].defence));
        }
        knapsack();
    }
    
    return 0;
}
```
