[UVa 301 Transportation](https://blog.csdn.net/metaphysis/article/details/161441539)

## 题目描述

运输公司 $\texttt{TransRuratania}$ 正在运营一列从 $A$ 城到 $B$ 城的特快列车，沿途设有多个停靠站。车站按顺序编号，$A$ 城为 $0$ 号站，$B$ 城为 $m$ 号站。列车最大载客量为 $n$ 人。

车票价格等于**起始站到终点站之间的车站数（包含终点站，不包含起点站）**。例如，从 $2$ 号站到 $5$ 号站，经过的车站为 $3$、$4$、$5$，共 $3$ 站，票价为 $3$。

在列车从 $A$ 城出发前，收集沿途各站的所有订票订单。每个订单包含三个整数：**起始站**、**终点站**、**乘客人数**。由于列车容量有限，公司可能无法接受所有订单。公司的拒绝策略是：**要么完全接受某个车站的全部订单，要么完全拒绝**（即不能拆分订单）。

要求：编写程序，给定列车容量 $n$、终点站编号 $m$ 以及所有订单，计算公司可能获得的最大总收益。单个订单的收益 = 乘客人数 × 票价，总收益为所有被接受订单的收益之和。

### 输入格式

输入文件由多个数据块组成。每个数据块的第一行包含三个整数：
- $n$：列车最大载客量
- $m$：终点站 $B$ 的编号
- $t$：订单数量

接下来 $t$ 行，每行一个订单，包含三个整数：起始站、终点站、乘客人数。

一个数据块中最多有 $22$ 个订单。$m$ 的值不超过 $7$。

输入以一行 `0 0 0` 结束。

### 输出格式

对于每个数据块（除结束块外），输出一行，包含可能的最大总收益。

### 样例输入

```
10 3 4
0 2 1
1 3 5
1 2 7
2 3 10
10 5 4
3 5 10
2 4 9
0 2 5
2 5 8
0 0 0
```

### 样例输出

```
34
```



## 题目分析

### 问题的本质

这是一个**带有容量约束的订单选择问题**。列车从起点到终点沿途经过多个车站，每个订单对应一段区间 $[start, end)$（乘客从 $start$ 站上车，$end$ 站下车）。列车容量 $n$ 限制了**任意时刻车上的人数**不能超过 $n$。

关键约束：
- 订单不可拆分
- 全程任意时刻车上人数 ≤ $n$
- 目标是最大化总收益

### 与经典问题的联系

这个问题可以看作是一个**区间调度**与**背包问题**的混合体，但具有以下特殊性质：
1. 车站数量很小（$m \leq 7$）
2. 订单数量最多 $22$ 个
3. 容量约束是全局的，需要在所有时间段内满足

由于 $m$ 很小，我们可以将列车路线划分为 $m$ 个**路段**（$\texttt{segment}$）：
- 路段 $j$ 表示从车站 $j$ 到车站 $j+1$ 的这一段行程
- 每个路段上的乘客数量 = 所有覆盖该路段的订单的乘客人数之和
- 每个路段的容量约束：乘客数 ≤ $n$

### 暴力搜索的可行性

订单数量最多 $22$，每个订单有“接受”或“拒绝”两种状态，总状态数为 $2^{22} \approx 4 \times 10^6$，直接枚举在时间上可行，但需要检查每个状态是否满足容量约束。然而，$4 \times 10^6 \times 22$ 约 $10^8$ 次操作，在 $1990$ 年代的 UVa 评测环境下可能较慢。因此需要**剪枝优化**。

本题的官方解法通常采用**深度优先搜索（$\texttt{DFS}$）** + 剪枝。

---

## 解题思路

### 步骤一：数据预处理

对于每个订单，计算：
- `money` = $(end - start) \times passenger$：该订单被接受时的收益
- `sumOfRemain`：从当前订单开始到最后一个订单的收益之和（用于剪枝）

对订单按**起始站**排序，若起始站相同则按**终点站**排序。排序的目的是使搜索过程更有序，便于剪枝。

### 步骤二：状态表示

搜索过程中需要维护：
- `passengers[i]`：在车站 $i$ **下车**的乘客数量
- `total`：当前车上的人数
- `money`：当前已获得的总收益
- `current`：当前正在处理的订单索引

关键技巧：**仅记录下车人数**。当列车到达一个车站时，先让该站下车的乘客离开，再考虑上车的订单。这样可以准确维护车上人数。

### 步骤三：搜索框架

```cpp
void dfs(int current, int previous, int total, int money)
```

参数说明：
- `current`：当前考虑的第 `current` 个订单
- `previous`：上一个被处理的订单的起始站（用于乘客下车更新）
- `total`：当前车上人数
- `money`：当前已获得的总收益

### 步骤四：乘客下车更新

在考虑当前订单之前，需要先让之前上车的乘客在到达当前订单的起始站时下车：

```cpp
for (int j = previous + 1; j <= allOrders[current].start; j++)
    total -= passengers[j];
```

这表示：从 `previous + 1` 站到 `current.start` 站，每站都有乘客下车（这些乘客之前在该站下车的数据已经记录在 `passengers` 数组中）。

### 步骤五：分支选择

对于每个订单，有两个分支：

1. **接受订单**：如果 `total + passenger ≤ n`，则接受。更新：
   - `passengers[end] += passenger`
   - `total += passenger`
   - `money += order.money`
   - 递归到下一个订单

2. **拒绝订单**：直接递归到下一个订单

### 步骤六：剪枝优化

使用**剩余收益上界剪枝**：

```cpp
if (money + allOrders[current].sumOfRemain <= maxMoney)
    return;
```

其中 `sumOfRemain` 是从当前订单到最后一个订单的收益之和。即使后续所有订单都被接受，总收益也不会超过 `money + sumOfRemain`。如果这个值已经不大于当前已知的最优解 `maxMoney`，则无需继续搜索。

### 步骤七：排序与预处理

排序后，从后向前计算 `sumOfRemain`：

```cpp
for (int i = orders - 2; i >= 0; i--)
    allOrders[i].sumOfRemain += allOrders[i + 1].sumOfRemain;
```

这保证了 `sumOfRemain` 是后缀收益的准确上界。

---

## 算法复杂度分析

### 时间复杂度

- 最坏情况：$2^{22} \approx 4 \times 10^6$ 个状态
- 每个状态需要 $O(m)$ 时间更新下车乘客（$m \leq 7$，可视为常数）
- 配合剪枝，实际运行效率远高于最坏情况
- UVa 评测时间：$0.000$ 秒

### 空间复杂度

- `passengers` 数组大小 $O(m)$
- `allOrders` 数组大小 $O(orders)$，最多 $22$
- 总空间复杂度 $O(1)$

---

## 正确性证明

**引理 1**：在搜索过程中，`total` 始终表示当前车上的人数。

证明：初始时 `total = 0`。每次到达一个车站，首先让在该站下车的乘客离开（从 `total` 中减去）。然后如果接受新订单，增加上车人数。由于下车乘客总是先于上车乘客被处理，`total` 始终准确反映车上人数。$\square$

**引理 2**：`passengers[i]` 记录的是在车站 $i$ 下车的乘客总数。

证明：每当接受一个从 $s$ 到 $e$ 的订单时，`passengers[e] += passenger`。这些乘客将在到达车站 $e$ 时被从 `total` 中减去。由于所有乘客的终点站都是明确的，这种记录方式正确。$\square$

**引理 3**：剪枝条件 `money + sumOfRemain <= maxMoney` 是安全的。

证明：`sumOfRemain` 是从当前订单到最后一个订单的收益之和，是后续订单可能贡献的最大收益（因为所有收益非负）。因此，即使后续订单全部被接受，总收益也不会超过 `money + sumOfRemain`。如果这个值 ≤ 已知最优解，则当前分支不可能产生更优解。$\square$

由引理 $1-3$，算法在有限状态空间中正确搜索最优解，剪枝不会导致遗漏更优解。

---

## 参考代码

```cpp
// Transportation
// UVa ID: 301
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct order {
    int start, end, passenger, money, sumOfRemain;
    
    // 按起始站排序，起始站相同按终点站排序
    bool operator<(order x) const {
        if (start != x.start)
            return start < x.start;
        else
            return end < x.end;
    }
};

int n, stations, orders, maxMoney = 0;
order allOrders[30];
int passengers[20];  // 记录每个车站下车的乘客人数

// 深度优先搜索
// current: 当前处理的订单索引
// previous: 上一个订单的起始站
// total: 当前车上人数
// money: 当前已获得收益
void dfs(int current, int previous, int total, int money) {
    // 所有订单处理完毕，更新最优解
    if (current == orders) {
        maxMoney = max(maxMoney, money);
        return;
    }
    
    // 剪枝：即使后续所有订单都接受，也无法超过当前最优解
    if (money + allOrders[current].sumOfRemain <= maxMoney)
        return;
    
    // 让乘客下车：从上一站之后到当前订单起始站之间的车站，乘客下车
    for (int j = previous + 1; j <= allOrders[current].start; j++)
        total -= passengers[j];
    
    // 分支1：接受当前订单（如果容量允许）
    if (total + allOrders[current].passenger <= n) {
        passengers[allOrders[current].end] += allOrders[current].passenger;
        dfs(current + 1, allOrders[current].start, 
            total + allOrders[current].passenger, 
            money + allOrders[current].money);
        passengers[allOrders[current].end] -= allOrders[current].passenger;  // 回溯
    }
    
    // 分支2：拒绝当前订单
    dfs(current + 1, allOrders[current].start, total, money);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    while (cin >> n >> stations >> orders) {
        if (n == 0 && stations == 0 && orders == 0)
            break;
        
        // 读取订单数据
        for (int i = 0; i < orders; i++) {
            cin >> allOrders[i].start >> allOrders[i].end >> allOrders[i].passenger;
            // 计算订单收益 = (终点站 - 起点站) * 乘客人数
            allOrders[i].money = (allOrders[i].end - allOrders[i].start) * allOrders[i].passenger;
            allOrders[i].sumOfRemain = allOrders[i].money;
        }
        
        // 按起始站排序
        sort(allOrders, allOrders + orders);
        
        // 计算后缀收益和，用于剪枝
        for (int i = orders - 2; i >= 0; i--)
            allOrders[i].sumOfRemain += allOrders[i + 1].sumOfRemain;
        
        // 初始化下车乘客数组
        for (int i = 0; i <= stations; i++)
            passengers[i] = 0;
            
        maxMoney = 0;
        dfs(0, 0, 0, 0);
        
        cout << maxMoney << endl;
    }
    
	return 0;
}
```

---

## 总结

本题的核心在于：
1. **状态建模**：用 `passengers` 数组记录下车人数，用 `total` 维护车上人数
2. **搜索框架**：$\texttt{DFS}$ 枚举每个订单的接受/拒绝
3. **剪枝优化**：利用后缀收益和进行可行性剪枝

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 容量约束 | 全程任意路段车上人数 ≤ $n$ |
| 乘客下车 | 到达车站时先下车，后上车 |
| 订单排序 | 按起始站排序，使搜索更有序 |
| 剪枝策略 | 后缀收益和上界剪枝 |
| 回溯 | 接受订单后需要恢复 `passengers` 数组 |

### 复杂度对比

| 方法 | 状态数 | 可行性 |
|------|--------|--------|
| 朴素枚举 | $2^{22} \approx 4 \times 10^6$ | 可行但较慢 |
| $\texttt{DFS}$ + 剪枝 | 远小于 $4 \times 10^6$ | 高效 |

这种“区间调度 + 容量约束 + $\texttt{DFS}$ 剪枝”的解题模式，在处理类似的车票预订、资源分配问题时具有通用性。
