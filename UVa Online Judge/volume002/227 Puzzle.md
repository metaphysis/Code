[UVa 227 Puzzle](https://blog.csdn.net/metaphysis/article/details/161087346)

## 题目分析

本题是一个经典的 $5 \times 5$ 滑动拼图问题。一个 $5 \times 5$ 的框架中包含了 $24$ 个印有字母的小方块和一个空白位置。可以通过将空白位置上下左右的相邻方块滑入空白处来改变拼图的布局。题目会给出拼图的初始布局以及一系列移动指令，要求输出最终布局。如果移动过程中出现非法移动（例如试图将边界外的方块移入空白），则输出无解信息。

**输入格式**：
- 每个测试用例由 $5$ 行初始布局开始，每行恰好 $5$ 个字符，空白位置用空格表示。
- 随后是多行移动指令，由 `A`（上）、`B`（下）、`L`（左）、`R`（右）组成，以字符 `0` 表示指令结束。
- 整个输入以字符 `Z` 作为结束标志。

**输出格式**：
- 每个测试用例输出 `Puzzle #x:`，其中 `x` 从 $1$ 开始。
- 若无解，输出 `This puzzle has no final configuration.`。
- 若有解，输出 $5$ 行，每行 $5$ 个字符，字符之间用一个空格分隔。

## 解题思路

本题的核心是模拟空白位置的移动过程。我们可以用一个 $5 \times 5$ 的字符数组存储拼图状态，并记录空白位置的坐标 $(x, y)$。

移动规则如下：
- `A`：空白位置向上移动，即与其上方的方块交换（$x-1, y$）。
- `B`：空白位置向下移动（$x+1, y$）。
- `L`：空白位置向左移动（$x, y-1$）。
- `R`：空白位置向右移动（$x, y+1$）。

如果移动后的新坐标超出 $0 \sim 4$ 的范围，则该移动非法。

### 输入处理细节

本题的输入格式比较特殊，需要注意以下几点：
1. 初始布局的每一行可能因为空白在行首而导致 `getline` 读入的长度不足 $5$，此时需要在行首补一个空格。
2. 移动指令可能跨越多行，需要持续读入直到遇到 `0`。
3. 不同测试用例之间不需要额外处理空行，但输出时每个测试用例后要跟一个空行（最后一个除外）。

### 算法步骤

1. 循环读入每个测试用例的第一个字符，若为 `Z` 则结束。
2. 读入 $5$ 行布局，同时找到空白位置坐标。
3. 读入移动指令直到遇到 `0`，对每个合法指令进行模拟。若遇到非法指令，标记无效。
4. 根据标记输出结果。

## 代码实现

```cpp
// Puzzle
// UVa ID: 227
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[5][5];   // 存储拼图布局
char direction;     // 当前移动指令
int x, y;           // 空白位置坐标
string directions = "LARB";  // 移动指令字符串，顺序对应 step 数组
// 方向数组，顺序：左、上、右、下
int step[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

// 模拟一次移动，返回是否合法
bool move()
{
    // 查找当前指令在 directions 中的索引
    int index = directions.find(direction);
    if (index == directions.npos)
        return false;
        
    // 计算移动后空白的新位置
    int xx = x + step[index][0];
    int yy = y + step[index][1];
    
    // 检查新位置是否越界
    if (xx < 0 || xx >= 5 || yy < 0 || yy >= 5)
        return false;
        
    // 交换空白与相邻方块
    board[x][y] = board[xx][yy];
    board[xx][yy] = ' ';
    x = xx;
    y = yy;
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases = 0;
    char input;
    string line;
    
    // 循环读取每个测试用例，以 'Z' 结束
    while (cin >> input, input != 'Z')
    {
        // 将读入的首字符放回，以便完整读取第一行布局
        cin.putback(input);
        
        // 读取 5 行初始布局
        for (int i = 0; i < 5; i++)
        {
            getline(cin, line);
            // 若长度不足 5，说明空白在行首，需要补一个空格
            if (line.length() < 5)
                line = ' ' + line;
            for (int j = 0; j < line.length(); j++)
            {
                board[i][j] = line[j];
                // 记录空白位置
                if (line[j] == ' ')
                {
                    x = i;
                    y = j;
                }
            }
        }
        
        // 相邻测试用例之间输出空行
        if (cases++)
            cout << "\n";
        
        cout << "Puzzle #" << cases << ":\n";
        
        bool invalid = false;
        // 读取移动指令，直到 '0'
        while (cin >> direction, direction != '0')
        {
            // 如果尚未非法，且当前移动非法，则标记
            if (invalid == false && move() == false)
                invalid = true;
        }
        
        // 输出结果
        if (invalid)
            cout << "This puzzle has no final configuration.\n";
        else
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j  = 0; j < 5; j++)
                {
                    if (j > 0)
                        cout << " ";
                    cout << board[i][j];
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
```
