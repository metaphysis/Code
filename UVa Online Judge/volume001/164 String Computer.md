[UVa 164 String Computer](https://blog.csdn.net/metaphysis/article/details/158732787)

## 题目分析

本题要求将源字符串通过最少的操作转换为目标字符串，可用的操作只有三种：
- **删除**：删除某个位置的字符
- **插入**：在某个位置插入一个字符
- **更改**：将某个位置的字符改为另一个字符

每个操作都需要输出对应的指令，格式为：
- 删除：$\texttt{D}$ + 字符 + 两位数字位置
- 插入：$\texttt{I}$ + 字符 + 两位数字位置
- 更改：$\texttt{C}$ + 字符 + 两位数字位置

程序以 $\texttt{E}$ 结尾。

## 解题思路

这是一个典型的**编辑距离**问题，可以使用**动态规划**求解。与普通的编辑距离不同的是，我们不仅需要计算最少操作次数，还需要**记录具体的操作序列**。

### 状态定义

定义 $dp[i][j]$ 表示将源字符串的前 $i$ 个字符转换为目标字符串的前 $j$ 个字符所需的最少操作次数。

同时，我们需要记录每个状态是由哪个操作转移而来的，以便后续回溯得到完整的操作序列。

### 状态转移

设源字符串为 $S$，目标字符串为 $T$，长度分别为 $M$ 和 $N$。

1. **初始化**：
   - $dp[0][0] = 0$，空串到空串不需要任何操作
   - $dp[i][0] = i$，表示将 $S$ 的前 $i$ 个字符全部删除
   - $dp[0][j] = j$，表示在空串中插入 $T$ 的前 $j$ 个字符

2. **状态转移方程**：
   对于 $i \geq 1$，$j \geq 1$：
   - **删除**：$dp[i][j] = dp[i-1][j] + 1$，删除 $S[i]$
   - **插入**：$dp[i][j] = dp[i][j-1] + 1$，插入 $T[j]$
   - **匹配/更改**：
     - 如果 $S[i] == T[j]$，则 $dp[i][j] = dp[i-1][j-1]$（匹配，不需要操作）
     - 否则 $dp[i][j] = dp[i-1][j-1] + 1$（更改）

   取上述三种操作中的最小值。

### 操作回溯

在动态规划的过程中，我们需要用另一个数组记录每个状态 $dp[i][j]$ 是由哪种操作得到的：
- $\texttt{DELETE}$：删除操作
- $\texttt{INSERT}$：插入操作
- $\texttt{CHANGE}$：更改操作
- $\texttt{MATCH}$：匹配（无需操作）

从 $dp[M][N]$ 开始回溯到 $dp[0][0]$，反向得到操作序列，最后输出时需要注意：
- **删除**：指令中的位置是删除时的当前位置，需要动态计算
- **插入**：指令中的位置是插入的目标位置
- **更改**：指令中的位置是目标位置

### 位置计算的关键点

在回溯过程中，由于插入和删除会影响字符串的长度和位置，需要特别注意：
- 删除操作的位置 = 当前源字符串中的位置 + 已经插入的字符数 - 已经删除的字符数
- 插入操作的位置 = 目标位置
- 更改操作的位置 = 目标位置

### 算法步骤

1. 读入源字符串 $S$ 和目标字符串 $T$
2. 在字符串前加空格，使索引从 $1$ 开始（方便处理）
3. 初始化 $dp$ 数组和操作记录数组
4. 三重循环计算 $dp$ 值：
   - 外层循环 $i$ 从 $1$ 到 $M$
   - 内层循环 $j$ 从 $1$ 到 $N$
   - 分别计算删除、插入、更改/匹配的代价，取最小值并记录操作
5. 从 $dp[M][N]$ 回溯到 $dp[0][0]$，输出操作序列
6. 最后输出 $\texttt{E}$ 表示程序结束

## 代码实现

```cpp
// String Computer
// UVa ID: 164
// Verdict: Accepted
// Submission Date: 2016-02-12
// UVa Run Time: 0.019s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NONE = -1, DELETE = 0, INSERT = 1, CHANGE = 2, MATCH = 3;

struct cell { int cost, operation; };

cell cells[25][25];
string S, T, operationCode = "DIC";
int M, N, deletions, insertions;

void displayPath(int i, int j) {
    if (cells[i][j].operation >= DELETE && cells[i][j].operation <= CHANGE) {
        cout << operationCode[cells[i][j].operation];
        if (cells[i][j].operation == CHANGE) {
            cout << T[j];
            cout << setw(2) << setfill('0') << j;
        }
        else if (cells[i][j].operation == DELETE) {
            cout << S[i];
            cout << setw(2) << setfill('0') << (i + insertions - deletions);
            deletions++;
        }
        else if (cells[i][j].operation == INSERT) {
            cout << T[j];
            cout << setw(2) << setfill('0') << j;
            insertions++;
        }
    }
}

void findPath(int i, int j) {
    if (cells[i][j].operation != NONE) {
        if (cells[i][j].operation == DELETE)
            findPath(i - 1, j);
        else if (cells[i][j].operation == INSERT)
            findPath(i, j - 1);
        else
            findPath(i - 1, j - 1);
    }
    displayPath(i, j);
}

void med() {
    S = ' ' + S;
    T = ' ' + T;
    M = S.length() - 1;
    N = T.length() - 1;

    cells[0][0] = (cell){0, NONE};
    for (int i = 1; i <= M; i++) cells[i][0] = (cell){i, DELETE};
    for (int j = 1; j <= N; j++) cells[0][j] = (cell){j, INSERT};

    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++) {
            cells[i][j] = (cell){cells[i - 1][j].cost + 1, DELETE};
            if (cells[i][j].cost > (cells[i][j - 1].cost + 1))
                cells[i][j] = (cell){cells[i][j - 1].cost + 1, INSERT};
            if (S[i] == T[j]) {
                if (cells[i][j].cost > cells[i - 1][j - 1].cost)
                    cells[i][j] = (cell){cells[i - 1][j - 1].cost, MATCH};
            } else {
                if (cells[i][j].cost > (cells[i - 1][j - 1].cost + 1))
                    cells[i][j] = (cell){cells[i - 1][j - 1].cost + 1, CHANGE};
            }
        }

    deletions = insertions = 0;
    findPath(M, N);
    cout << "E" << endl;
}

int main() {
    while (cin >> S, S != "#" && cin >> T) med();
    return 0;
}
```

## 样例验证

输入：
```
abcde bcgfe
#
```

输出：
```
Da01Cg03If04E
```

与题目给出的样例完全一致，说明算法正确。

## 复杂度分析

- **时间复杂度**：$O(M \times N)$，其中 $M$ 和 $N$ 分别是源字符串和目标字符串的长度，最大为 $20$，因此计算量很小。
- **空间复杂度**：$O(M \times N)$，用于存储 $dp$ 表和操作记录。

## 总结

本题是编辑距离问题的变种，难点在于**操作序列的记录和位置的动态计算**。通过动态规划求解最小编辑距离，并记录每个状态的操作来源，最后回溯得到完整的操作序列即可。位置计算时需要考虑插入和删除对字符串长度的影响，这是本题最容易出错的地方。
