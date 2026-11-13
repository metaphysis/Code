[UVa 232 Crossword Answers](https://blog.csdn.net/metaphysis/article/details/161207735)

## 题目分析

本题是一个填字游戏（$\texttt{Crossword Puzzle}$）的题目。给定一个 $r \times c$ 的网格，其中白色格子包含字母，黑色格子用 $\texttt{*}$ 表示。需要按照规则对白色格子进行编号，并分别输出 **`Across`**（横向）和 **`Down`**（纵向）的单词列表。

### 编号规则

一个白色格子是 **`eligible`**（可编号）的条件为：

1. 该格子位于第一行（$i = 0$）；
2. 或者该格子位于第一列（$j = 0$）；
3. 或者该格子左边的格子（同一行，前一列）是黑色格子（$\texttt{*}$）；
4. 或者该格子上边的格子（同一列，前一行）是黑色格子（$\texttt{*}$）。

所有符合条件的格子按行优先顺序依次编号，从 $1$ 开始。

### 单词定义规则

- **`Across` 单词**：从一个编号格开始，向右连续取字母，直到遇到黑色格子或行末结束。
- **`Down` 单词**：从一个编号格开始，向下连续取字母，直到遇到黑色格子或列末结束。

## 解题思路

1. **读入数据**：读入网格的行数 $r$ 和列数 $c$，当 $r = 0$ 且 $c = 0$ 时结束输入。

2. **编号阶段**：
   - 遍历整个网格，对每个白色格子判断是否符合编号条件。
   - 使用一个二维数组 $\texttt{indexer}$ 记录每个白色格子的编号（初始为 $0$）。
   - 使用另一个二维数组 $\texttt{backup}$ 备份编号，用于输出 `Down` 单词时使用（因为输出 `Across` 时会修改 $\texttt{indexer}$ 的值）。

3. **输出 `Across` 单词**：
   - 按行优先顺序遍历网格。
   - 如果当前格子有编号（$\texttt{indexer}[i][j] \neq 0$），则：
     - 输出编号（右对齐，宽度为 $3$）；
     - 从当前位置开始向右输出连续的字母，直到遇到 $\texttt{*}$ 或行末；
     - 同时将已输出的格子对应的 $\texttt{indexer}$ 置为 $0$，避免重复输出。

4. **输出 `Down` 单词**：
   - 按行优先顺序遍历网格。
   - 如果当前格子有备份编号（$\texttt{backup}[i][j] \neq 0$），则：
     - 输出编号（右对齐，宽度为 $3$）；
     - 从当前位置开始向下输出连续的字母，直到遇到 $\texttt{*}$ 或列末；
     - 同时将已输出的格子对应的 $\texttt{backup}$ 置为 $0$。

5. **格式要求**：
   - 每个测试用例输出前先打印 $\texttt{puzzle \#x:}$，其中 $x$ 从 $1$ 开始。
   - `Across` 和 `Down` 列表分别以 $\texttt{Across}$ 和 $\texttt{Down}$ 作为标题。
   - 相邻两个测试用例的输出之间用空行分隔。

## 代码实现

```cpp
// Crossword Answers
// UVa ID: 232
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[10][10];      // 存储网格，最多10x10
int indexer[10][10];     // 存储每个白色格子的编号（输出Across时使用）
int backup[10][10];      // 备份编号（输出Down时使用）

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int r, c, cases = 0;    // r行数，c列数，cases记录当前是第几个测试用例
    
    // 当r和c均为0时结束输入
    while (cin >> r >> c, r && c)
    {
        // 读入网格数据
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cin >> board[i][j];
                indexer[i][j] = 0;    // 初始化编号为0
                backup[i][j] = 0;     // 初始化备份为0
            }
        }
        
        // 第一遍遍历：为符合条件的白色格子编号
        int counter = 1;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                // 只处理白色格子（非'*'）
                if (board[i][j] != '*')
                {
                    // 判断是否为eligible格子：
                    // 1. 位于第一行（i == 0）
                    // 2. 位于第一列（j == 0）
                    // 3. 左边格子是黑色（board[i][j-1] == '*'）
                    // 4. 上边格子是黑色（board[i-1][j] == '*'）
                    if (i == 0 || j == 0 ||
                        (board[i - 1][j] == '*') || (j > 0 && board[i][j - 1] == '*'))
                        {
                            indexer[i][j] = counter++;    // 分配编号
                            backup[i][j] = indexer[i][j]; // 备份编号
                        }
                }
            }
        }

        // 如果不是第一个测试用例，输出空行分隔
        if (cases++)
            cout << "\n";
            
        // 输出测试用例标题
        cout << "puzzle #" << cases << ":" << "\n";
        
        // 输出Across单词
        cout << "Across" << endl;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (indexer[i][j])    // 如果当前格子有编号
                {
                    // 输出编号，宽度为3，右对齐
                    cout << setw(3) << right << indexer[i][j] << ".";
                    // 向右输出连续的字母
                    for (int k = j; k < c && board[i][k] != '*'; k++)
                    {
                        cout << board[i][k];
                        indexer[i][k] = 0;    // 标记已输出，避免重复
                    }
                    cout << "\n";
                }
        
        // 输出Down单词
        cout << "Down" << "\n";
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (backup[i][j])    // 如果当前格子有备份编号
                {
                    // 输出编号，宽度为3，右对齐
                    cout << setw(3) << right << backup[i][j] << ".";
                    // 向下输出连续的字母
                    for (int k = i; k < r && board[k][j] != '*'; k++)
                    {
                        cout << board[k][j];
                        backup[k][j] = 0;    // 标记已输出，避免重复
                    }
                    cout << "\n";
                }        
    }
    
    return 0;
}
```
