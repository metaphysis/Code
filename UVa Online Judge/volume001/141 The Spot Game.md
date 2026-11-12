[UVa 141 The Spot Game](https://blog.csdn.net/metaphysis/article/details/157463790)

## 题目分析

$\texttt{The Spot Game}$ 是一个基于 $N \times N$ 棋盘的游戏，双方轮流执行操作，操作包括：

- 在空白格子中放置一个黑子（用 “+” 表示）；
- 从棋盘上移除一个已有的黑子（用 “-” 表示）。

游戏规则如下：

- 如果当前棋盘状态（或其旋转 $90°$、$180°$ 后的状态）在之前的游戏过程中已经出现过，则当前玩家立即输掉游戏，对方获胜；
- 游戏最多进行 $2N$ 步；
- 如果在 $2N$ 步后仍未出现重复状态，则游戏平局。

输入包含多组游戏，每组游戏的第一行为棋盘大小 $N$（$2 \leq N \leq 50$），接下来是 $2N$ 行操作，每行包含坐标 $(x, y)$ 和操作符 `+` 或 `-`。输入以 $0$ 结束。

输出应指出获胜的玩家和获胜的步数，或声明游戏平局。

## 解题思路

### 核心问题
我们需要高效地检测棋盘状态是否重复（包括旋转后的状态）。由于棋盘最大可达 $50 \times 50$，直接表示状态矩阵并比较的复杂度较高，但我们可以将状态编码成字符串进行存储和比较。

### 状态编码
我们可以用一个长度为 $N \times N$ 的字符串表示棋盘状态：
- 用 `‘1’` 表示该位置有黑子；
- 用 `‘0’` 表示该位置为空。

每次操作后，更新对应的字符。

### 旋转处理
题目要求判断当前状态是否与之前任一状态在旋转 $0°$、$90°$（顺时针）、$90°$（逆时针）或 $180°$ 后相同。因此，我们需要编写函数，分别生成当前状态的三种旋转状态。

为了便于比较，我们始终将旋转后的状态也编码为字符串，并存储到集合中。

### 查找重复
使用哈希表（如 `map<string, int>`）存储所有出现过的状态（包括旋转后的状态），值为首次出现时的步数。

每步操作后，生成当前状态的四个等价状态（原状态 + 三种旋转），检查它们是否已经在哈希表中：
- 如果存在，则当前玩家输，对方获胜；
- 否则，将这四个状态插入哈希表，记录当前步数。

### 时间复杂度
每一步需要生成四个字符串，长度均为 $N^2$，最多 $2N$ 步，因此总时间复杂度约为 $O(N^3)$，在 $N \leq 50$ 时是可接受的。

## 代码实现说明

以下代码使用 $\texttt{C++}$ 编写，主要步骤包括：

1. 读取 $N$，若为 0 则结束；
2. 初始化状态字符串和哈希表；
3. 循环处理 $2N$ 步操作：
   - 更新棋盘状态；
   - 检查当前状态是否已出现；
   - 生成旋转状态并插入哈希表；
4. 根据是否出现重复状态输出结果。

## 参考代码

```cpp
// The Spot Game
// UVa ID: 141
// Verdict: Accepted
// Submission Date: 2016-01-20
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string rotateCW90(string matrix, int n) {
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) * n + (i - 1) - (j - 1) * n];
    return newMatrix;
}

string rotateCCW90(string matrix, int n) {
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) - (i - 1) + (j - 1) * n];
    return newMatrix;
}

string rotate180(string matrix) {
    reverse(matrix.begin(), matrix.end());
    return matrix;
}

int main() {
    int n, x, y;
    string line;
    map<string, int> steps;
    while (cin >> n, n) {
        int winner = 0, move = 0;
        string matrix = string(n * n, '0');
        steps.clear();
        for (int i = 1; i <= 2 * n; i++) { 
            cin >> x >> y;
            getline(cin, line);
            if (winner > 0) continue;
            matrix[(x - 1) * n + (y - 1)] = (line.find('+') != line.npos) ? '1' : '0';
            if (steps.find(matrix) != steps.end()) {
                winner = (steps[matrix] % 2 == 1) ? 2 : 1;
                move = i;
            }
            string newMatrix[4] = {
                matrix,
                rotateCW90(matrix, n), rotateCCW90(matrix, n),
                rotate180(matrix)
            };
            for (int j = 0; j < 4; j++)      
                if (steps.find(newMatrix[j]) == steps.end())
                    steps.insert(make_pair(newMatrix[j], i));
        }
        if (winner == 0) cout << "Draw\n";
        else cout << "Player " << winner << " wins on move " << move << '\n';
    }
	return 0;
}
```
