[UVa 124 Following Orders](https://blog.csdn.net/metaphysis/article/details/156709560)

## 题目描述

给定一组形式为 $x < y$ 的变量约束条件，要求输出所有满足这些约束条件的变量排列。变量均为单个小写字母，每个测试用例包含至少 $2$ 个、至多 $20$ 个变量，以及至少 $1$ 个、至多 $50$ 个约束条件。满足条件的排列数量在 $1$ 到 $300$ 之间。输入以文件结束（$\texttt{EOF}$）终止，每个测试用例的输出之间用空行分隔，排列需按字典序（字母序）输出。

## 输入格式

每个测试用例由两行组成：
- 第一行：变量列表（字符间用空格分隔）
- 第二行：约束条件列表，每对 $x \\ y$ 表示 $x < y$

## 输出格式

每个测试用例输出所有满足约束的排列，每行一个，按字典序排列。不同测试用例的输出之间用一个空行分隔。

## 样例输入

```
a b f g
a b b f
w u x y z
v y x v z v w v
```

## 样例输出

```
abfg
abgf
agbf
gabf

wzxyy
wzxyy
xwzyy
xzwyy
zuxvy
zxwy
```

## 题目分析

本题本质上是**拓扑排序**的枚举问题：给定一个有向图（变量为节点，约束 $x < y$ 为有向边 $x \to y$），要求输出所有可能的拓扑序列，且按字典序输出。

由于变量数量最多为 $20$，约束最多为 $50$，可能的排列数不超过 $300$，因此我们可以采用**回溯法（$\texttt{Backtracking}$）** 结合**剪枝**来生成所有满足条件的排列。

### 核心思路

1. **建模**：
   - 将变量视为图中的节点。
   - 每个约束 $x < y$ 对应一条从 $x$ 指向 $y$ 的有向边。
   - 我们需要输出所有拓扑排序（即满足所有约束的线性顺序）。

2. **算法选择**：
   - 使用深度优先搜索（$\texttt{DFS}$）回溯生成排列。
   - 在生成排列的过程中，检查当前部分排列是否违反约束，若违反则提前剪枝。
   - 为了按字典序输出，首先对变量列表进行排序，然后在回溯时按顺序尝试变量。

3. **剪枝策略**：
   - 记录每个变量在已生成排列中的位置。
   - 每添加一个变量，检查所有约束条件：如果某个约束 $x < y$ 中 $x$ 和 $y$ 都已出现在排列中，且 $x$ 的位置大于等于 $y$ 的位置，则当前排列无效，回溯。
   - 这样可以在早期排除无效分支，减少搜索空间。

4. **时间复杂度**：
   - 最坏情况下需要生成所有拓扑排序，数量不超过 $300$，回溯搜索的剪枝效果较好，实际运行效率可以接受。

## 解题步骤

1. 读取变量列表，排序以保证输出字典序。
2. 读取约束条件，存储为边的列表。
3. 初始化访问标记数组 $\texttt{visited}$ 和位置数组 $\texttt{value}$。
4. 从第一个位置开始回溯生成排列：
   - 若当前排列长度达到 $n$，输出。
   - 否则，按变量顺序尝试每个未使用的变量，放入当前位。
   - 更新位置信息，检查约束是否满足。
   - 递归下一层，回溯时恢复状态。
5. 每个测试用例输出后打印空行（最后一个除外）。

## 代码实现

```cpp
// Following Orders
// UVa ID: 124
// Verdict: Accepted
// Submission Date: 2015-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20

bool visited[MAXN];
int nChar, value[2 * MAXN], nLimit;
char output[MAXN], input[MAXN], limit[MAXN][2];

void print() {
    for (int i = 0; i < nChar; i++)
        cout << output[i];
    cout << endl;
}

bool isValid() {
    for (int i = 0; i < nLimit; i++)
        if (value[limit[i][0] - 'a'] >= 0 &&
            value[limit[i][1] - 'a'] >= 0 &&
            value[limit[i][0] - 'a'] > value[limit[i][1] - 'a'])
            return false;
    return true;
}

void lexicographical(int current) {
    if (current >= 2 && !isValid()) return;
    if (current == nChar) {
        print();
        return;
    }
    for (int i = 0; i < nChar; i++)
        if (!visited[i]) {
            visited[i] = true;
            output[current] = input[i];
            value[input[i] - 'a'] = current;
            lexicographical(current + 1);
            value[input[i] - 'a'] = -1;
            visited[i] = false;
        }
}

bool cmp(char a, char b) { return a < b; }

int main(int ac, char *av[]) {
    string line;
    int cases = 0;
    while (getline(cin, line), line.length() > 0) {
        // 输出间隔空行。
        if (cases > 0) cout << endl;
        // 读取字符，初始化相关变量。
        istringstream first(line);
        nChar = 0;
        while (first >> input[nChar]) {
            output[nChar] = 0;
            visited[nChar] = false;
            nChar++;
        }
        for (int i = 0; i < 2 * MAXN; i++) value[i] = -1;
        sort(input, input + nChar, cmp);
        // 读取限制。
        nLimit = 0;
        getline(cin, line);
        istringstream next(line);
        while (next >> limit[nLimit][0]) next >> limit[nLimit++][1];
        // 使用回溯生成字典序排列然后检查是否符合限制条件。
        lexicographical(0);
        cases++;
    }
    return 0;
}
```

## 总结

本题是一道典型的**拓扑排序枚举**问题，通过回溯法生成所有可能的排列，并利用约束条件进行剪枝，从而在合理时间内得到结果。需要注意输出格式（字典序、空行分隔）和边界条件（变量数、约束数、排列数）。代码实现简洁，剪枝策略有效，能够在给定的限制下快速求解。
