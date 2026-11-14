[UVa 387 A Puzzling Problem](https://blog.csdn.net/metaphysis/article/details/161673654)

## 题目描述

本题的目标是编写一个程序，接受 $1$ 到 $5$ 个拼图片（如下所示），并尝试将它们拼成一个 $4 \times 4$ 的正方形。拼图片不能旋转或翻转，必须全部使用。可能有多个解，任意一个均可。

### 输入格式

输入文件包含多个拼图（即多个拼图片集合）。第一行是第一个拼图中拼图片的数量。每个拼片由一行两个整数（行数和列数）和后续若干行指定形状。形状由 `0` 和 `1` 字符组成，`1` 表示拼片的实体部分。例如，拼片 A 的表示如下：

```
2 3
111
101
```

拼片按输入顺序编号（#1、#2 等）。所有拼片不超过 $4$ 行 $4$ 列。输入以拼图片数量为 $0$ 结束。

### 输出格式

输出一个 $4 \times 4$ 的正方形，每个位置用拼片编号填充。不同拼图的解之间用一个空行分隔。如果无解，输出 `No solution possible`。

### 样例输入

```
4
2 3
111
101
4 2
01
01
11
01
2 1
1
1
3 2
10
10
11
4
1 4
1111
1 4
1111
1 4
1111
2 3
111
001
5
2 2
11
11
2 3
111
100
3 2
11
01
01
1 3
111
1 1
0
```

### 样例输出

```
1112
1412
3422
3442

No solution possible

1133
1153
2223
2444
```

---

## 题目分析

### 问题的本质

这是一个**精确覆盖问题**（$\texttt{exact cover}$），类似于拼图游戏。需要将 $n$ 个拼片（$1 \leq n \leq 5$）放入 $4 \times 4$ 的网格中，每个拼片的实体部分占据 $1$ 个或多个格子，所有拼片必须恰好覆盖全部 $16$ 个格子，且不能重叠。

### 关键约束

- 拼片不能旋转或翻转
- 所有拼片的实体格子总数必须恰好为 $16$
- 拼片可以放置在网格的任何位置，只要不超出边界
- 拼片的 `0` 部分不占格子，只用于定义形状

### 搜索策略

使用深度优先搜索（$\texttt{DFS}$），按顺序放置拼片。对于每个拼片，尝试所有可能的位置（左上角坐标），检查是否与已放置的拼片重叠。如果成功放置，递归处理下一个拼片。

---

## 参考代码

```cpp
// A Puzzling Problem
// UVa ID: 387
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.170s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<pair<pair<int, int>, vector<int>>> pieces;  // 拼片：((行数,列数), 形状矩阵)
vector<bool> visited;                               // 拼片是否已使用
int grid[4][4];                                     // 网格

// 输出当前网格
void display()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

// 从网格中移除指定编号的拼片
void pullOut(int digit)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == (digit + 1))
                grid[i][j] = 0;
}

// 将拼片放入网格的指定位置
bool pushIn(int digit, int row, int column)
{
    // 检查是否超出边界
    if (row + pieces[digit].first.first > 4 || column + pieces[digit].first.second > 4) 
        return false;
    
    bool success = true;
    // 尝试放置
    for (int r = 0; r < pieces[digit].first.first; r++)
        for (int c = 0; c < pieces[digit].first.second; c++)
        {
            int block = pieces[digit].second[r * pieces[digit].first.second + c];
            if (grid[row + r][column + c] == 0)
                grid[row + r][column + c] = block;
            else if (block != 0)  // 重叠
            {
                success = false;
                goto out;
            }
        }

out:
    if (!success)
        pullOut(digit);
    return success;
}

// 深度优先搜索
bool dfs(int depth, int n)
{
    if (depth == n)  // 所有拼片都放置成功
    {
        display();
        return true;
    }

    for (int i = 0; i < visited.size(); i++)
        if (!visited[i])
        {
            visited[i] = true;
            for (int row = 0; row < 4; row++)
                for (int column = 0; column < 4; column++)
                    if ((grid[row][column] == 0 || pieces[i].second.front() == 0) && pushIn(i, row, column))
                    {
                        if (dfs(depth + 1, n))
                            return true;
                        pullOut(i);  // 回溯
                    }
            visited[i] = false;
        }
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0, row, column;
    string line;

    while (cin >> n, n)
    {
        pieces.clear();
        int cell = 0;  // 实体格子总数

        // 读取拼片
        for (int i = 1; i <= n; i++)
        {
            cin >> row >> column;
            vector<int> matrix;
            for (int j = 1; j <= row; j++)
            {
                cin >> line;
                cell += count(line.begin(), line.end(), '1');
                for (char c : line)
                    matrix.push_back(c == '1' ? i : 0);
            }
            pieces.push_back(make_pair(make_pair(row, column), matrix));
        }

        // 测试用例间空行
        if (cases++) cout << endl;

        // 快速检查：所有拼片的实体格子总数必须为 16
        if (cell != 16)
        {
            cout << "No solution possible" << endl;
            continue;
        }

        visited.resize(n);
        fill(visited.begin(), visited.end(), false);
        memset(grid, 0, sizeof(grid));

        if (!dfs(0, n))
            cout << "No solution possible" << endl;
    }

    return 0;
}
```
