[UVa 233 Package Pricing](https://blog.csdn.net/metaphysis/article/details/161207878)

## 题目分析

题目描述了一家销售 $4$ 种尺寸节能灯泡的公司，这些灯泡尺寸分别用字符 `'a'`、`'b'`、`'c'`、`'d'` 表示。公司提供若干优惠套餐，每个套餐有目录编号、价格和包含的灯泡组合。顾客需要购买特定数量的灯泡，要求找出最便宜的套餐组合方式，使得购买的灯泡数量满足或超过顾客需求，并输出总价和套餐清单。

## 解题思路

### 状态表示

本题需要使用状态压缩动态规划（$\texttt{DP}$），将 $4$ 种尺寸的需求量编码为一个状态。每种尺寸的需求量最多是多少？题目没有明确给出，但根据状态数组 `memo[1048576]` 可以推断，每种尺寸的最大需求量为 $20$（因为 $(20+1)^4 = 194481$ 远小于 $1048576$，实际测试发现最大需求量为 $20$）。使用 `base` 数组计算状态索引：

$$
index = count[0] \times base[0] + count[1] \times base[1] + count[2] \times base[2] + count[3] \times base[3]
$$

其中：

$$
\begin{aligned}
base[0] &= ( need[1] + 1 ) \times ( need[2] + 1 ) \times ( need[3] + 1 ) \\
base[1] &= ( need[2] + 1 ) \times ( need[3] + 1 ) \\
base[2] &= need[3] + 1 \\
base[3] &= 1
\end{aligned}
$$

### 动态规划转移

定义 `memo[state]` 存储三个信息：
- `price`：达到该状态的最小花费；
- `index`：达到该状态时最后选择的套餐编号；
- `parent`：达到该状态的前一个状态。

初始状态 `memo[0] = {0, -1, -1}`，其他状态初始化为极大值 `1E20`。

对于每个状态 `state`，解码出当前已购买的灯泡数量 `current[4]`。然后尝试添加每种套餐 `packages[i]`，得到新状态 `next`：

$$
next[j] = \min(current[j] + packages[i].supply[j],\ need[j])
$$

如果新状态的 `price` 大于当前状态花费加上套餐价格，则更新 `memo[next]`。

### 结果回溯

求出 `maxState = getIndex(need)` 后，`memo[maxState].price` 即为最小总价。然后从 `maxState` 开始回溯，记录每个状态使用的套餐，通过 `counter` 累加套餐的使用次数。最后输出结果时，套餐按目录编号升序输出，使用次数超过 $1$ 时用括号注明。

### 注意事项

- 由于顾客请求中可能包含重复尺寸，需要在输入时累加统计。
- 输出的价格保留两位小数，使用 `fixed` 和 `setprecision(2)`。
- 每个测试用例的 `counter` 在使用前需要清空。

## 代码实现

```cpp
// Package Pricing
// UVa ID: 233
// Verdict: Accepted
// Submission Date: 2016-06-21
// UVa Run Time: 0.460s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 套餐结构体
struct package
{
    int catalogue;      // 套餐编号
    double price;       // 套餐价格
    int supply[4];      // 四种尺寸灯泡的个数
};

// DP状态结构体
struct choice
{
    double price;       // 达到该状态的最小花费
    int index, parent;  // 最后选择的套餐编号和前一个状态
};

int n;                          // 套餐数量
vector<package> packages;       // 存储所有套餐
int base[4];                    // 用于状态编码的基数
double minPrice;                // 最小总价
map<int, int> counter;          // 统计每个套餐的使用次数
choice memo[1048576];           // DP状态数组

// 根据当前数量数组计算状态编码
int getIndex(int count[])
{
    int index = 0;
    for (int j = 0; j < 4; j++)
        index += count[j] * base[j];
    return index;
}

// 动态规划求解最便宜套餐组合
void dp(package need)
{
    // 计算基数数组
    base[0] = (need.supply[1] + 1) * (need.supply[2] + 1) * (need.supply[3] + 1);
    base[1] = (need.supply[2] + 1) * (need.supply[3] + 1);
    base[2] = need.supply[3] + 1;
    base[3] = 1;

    int current[4], next[4], maxState = getIndex(need.supply);

    // 初始化DP状态为极大值
    for (int i = 0; i <= maxState; i++)
        memo[i] = (choice){1E20, -1, -1};

    // 初始状态花费为0
    memo[0] = (choice){0, -1, -1};

    // 遍历所有状态
    for (int state = 0; state <= maxState; state++)
    {
        int s = state;
        // 解码当前状态，得到已购买的灯泡数量
        for (int i = 0; i < 4; i++)
            current[i] = s / base[i], s %= base[i];

        // 尝试每种套餐
        for (int i = 0; i < n; i++)
        {
            // 计算添加套餐i后的新状态
            for (int j = 0; j < 4; j++)
                next[j] = min(current[j] + packages[i].supply[j], need.supply[j]);

            int index = getIndex(next);

            // 如果新状态的花费可以更小，则更新
            if (memo[index].price > memo[state].price + packages[i].price)
                memo[index] = (choice){memo[state].price + packages[i].price, i, state};
        }
    }

    // 回溯统计套餐使用次数
    counter.clear();
    for (int state = maxState; state > 0; state = memo[state].parent)
        counter[packages[memo[state].index].catalogue]++;

    // 记录最小总价
    minPrice = memo[maxState].price;
}

int main()
{
    ios::sync_with_stdio(false);
    
    string line;

    while (getline(cin, line))
    {
        packages.clear();

        // 读取套餐数量
        n = stoi(line);

        // 读取n个套餐信息
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            istringstream iss(line);

            package p;
            iss >> p.catalogue >> p.price;

            // 初始化四种尺寸的数量为0
            memset(p.supply, 0, sizeof(p.supply));
            char size;
            int count;
            while (iss >> size >> count)
                p.supply[size - 'a'] += count;

            packages.push_back(p);
        }

        // 读取顾客请求数量
        getline(cin, line);
        int m = stoi(line);

        // 处理每个顾客请求
        for (int i = 1; i <= m; i++)
        {
            getline(cin, line);
            istringstream iss(line);

            package need;
            memset(need.supply, 0, sizeof(need.supply));
            
            char size;
            int count;
            while (iss >> size >> count)
                need.supply[size - 'a'] += count;

            dp(need);

            // 输出结果：请求编号、冒号、总价（右对齐宽度8）
            cout << i << ":" << setw(8) << right;
            cout << fixed << setprecision(2) << minPrice;

            // 输出套餐组合（按编号升序）
            for (auto c : counter)
            {
                if (c.second > 0) cout << " " << c.first;
                if (c.second > 1) cout << "(" << c.second << ")";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
```
