[UVa 410 Station Balance](https://blog.csdn.net/metaphysis/article/details/161762779)

## 题目描述

题目要求将 $S$ 个标本分配到 $C$ 个离心机室中，每个室最多可以容纳 $0$、$1$ 或 $2$ 个标本。分配的目标是最小化不平衡度 $\textit{IMBALANCE}$，其定义为：

$$
\textit{IMBALANCE} = \sum_{i = 1}^{C} |\textit{CM}_i - \textit{AM}|
$$

其中：
- $\textit{CM}_i$ 是第 $i$ 个室的总质量，即分配到该室的标本质量之和。
- $\textit{AM}$ 是所有室的平均质量，即所有标本总质量除以室数 $C$。

## 输入格式

输入包含多组数据。每组数据格式如下：
- 第一行包含两个整数 $C$ 和 $S$（$1 \le C \le 5$，$1 \le S \le 2C$），分别表示室数和标本数。
- 第二行包含 $S$ 个整数，表示每个标本的质量（$1$ 到 $1000$ 之间），由空格分隔。

## 输出格式

对于每组数据，首先输出一行 `Set #X`，其中 $X$ 从 $1$ 开始递增。接下来输出 $C$ 行，每行格式为：室号（第 $1$ 列）、冒号（第 $2$ 列）、然后从第 $4$ 列开始输出该室分配的标本质量，质量之间用恰好一个空格分隔。如果某室没有分配标本，则只输出室号和冒号，不输出质量。最后输出一行 `IMBALANCE = X`，其中 $X$ 为计算出的不平衡度，保留 $5$ 位小数。每组输出后跟一个空行。

## 样例

输入

```
2 3
6 3 8
3 5
51 19 27 14 33
5 9
1 2 3 5 7 11 13 17 19
```

输出

```
Set #1
 0: 6 3
 1: 8
IMBALANCE = 1.00000

Set #2
 0: 51
 1: 19 27
 2: 14 33
IMBALANCE = 6.00000

Set #3
 0: 1 17
 1: 2 13
 2: 3 11
 3: 5 7
 4: 19
IMBALANCE = 11.60000
```

## 题目分析

本题的核心是将 $S$ 个标本分配到 $C$ 个室中，每个室最多 $2$ 个标本，使得各室总质量与平均质量之差的绝对值之和最小。

### 问题转化

由于每个室最多放 $2$ 个标本，且 $S \le 2C$，因此有些室可能只放 $1$ 个标本或空置。为了简化处理，可以引入质量为 $0$ 的虚拟标本，使得标本总数恰好为 $2C$。这样每个室恰好分配到 $2$ 个标本（允许质量为 $0$），问题转化为将 $2C$ 个标本（包含虚拟的 $0$）两两配对，使得各对质量和与平均质量之差的绝对值之和最小。

### 最优配对策略

已知一个经典结论：对于此类两两配对使各对和尽量接近的问题，最优策略是将标本质量排序后，将最小的与最大的配对，次小的与次大的配对，依此类推。这是因为这种配对方式能够平衡各对的和，使它们尽可能接近。

具体步骤如下：
1. 将所有标本质量（包括补充的 $0$）按升序排序。
2. 将第 $i$ 小的与第 $i$ 大的配对（即 $\textit{masses}[i]$ 与 $\textit{masses}[2C - 1 - i]$ 配对），$i$ 从 $0$ 到 $C-1$。
3. 计算每个配对的和，然后计算与平均质量 $AM$ 的差的绝对值，累加得到 $\textit{IMBALANCE}$。

### 平均质量的计算

平均质量 $AM$ 定义为所有标本总质量除以室数 $C$。注意虚拟标本的质量 $0$ 不计入总质量，因此总质量即为原始标本质量之和。

### 输出格式

每个室输出时，需要按升序输出该室的两个标本质量（小的在前，大的在后）。由于配对时 $\textit{masses}[i] \le \textit{masses}[2C - 1 - i]$，因此可以直接先输出 $\textit{masses}[i]$，再输出 $\textit{masses}[2C - 1 - i]$。注意质量为 $0$ 的虚拟标本不应输出。

### 边界情况

- 如果 $S < 2C$，则需要补充 $2C - S$ 个 $0$。
- 如果某室的两个标本质量均为 $0$，则该室不输出任何质量（只输出室号和冒号）。
- 不平衡度需要保留 $5$ 位小数。

### 复杂度分析

每组数据排序复杂度 $O(2C \log(2C))$，$C \le 5$，可忽略。总复杂度 $O(T \times C \log C)$。

## 代码实现

```cpp
// Station Balance
// UVa ID: 410
// Verdict: Accepted
// Submission Date: 2016-07-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// http://www.algorithmist.com/index.php/UVa_410

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int chambers, specimens, mass, cases = 0;

    while (cin >> chambers >> specimens)
    {
        int total_masses = 0;
        vector<int> masses;
        for (int i = 1; i <= specimens; i++)
        {
            cin >> mass;
            masses.push_back(mass);
            total_masses += mass;
        }

        while (masses.size() < 2 * chambers) masses.push_back(0);

        sort(masses.begin(), masses.end());

        int average_masses = 0;
        cout << "Set #" << ++cases << '\n';
        for (int i = 0; i < chambers; i++)
        {
            cout << ' ' << i << ':';
            int a = masses[i], b = masses[2 * chambers - 1 - i];
            if (a > 0 || b > 0)
            {
                if (a > 0) cout << ' ' << a;
                if (b > 0) cout << ' ' << b;
            }
            cout << '\n';
            average_masses += abs((a + b) * chambers - total_masses);
        }
        cout << "IMBALANCE = ";
        cout << fixed << setprecision(5) << (double)average_masses / (double)chambers;
        cout << "\n\n";
    }

    return 0;
}
```