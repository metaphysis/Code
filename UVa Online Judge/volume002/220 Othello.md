[UVa 220 Othello](https://blog.csdn.net/metaphysis/article/details/161083263)

## 题目分析

本题一个模拟黑白棋（奥赛罗棋）游戏的问题。题目要求读取多个游戏对局，根据命令执行相应的操作，包括：

- **`L` 命令**：列出当前玩家所有合法的落子位置，按行主序输出
- **`Mxy` 命令**：在指定位置落子，并翻转被夹住的棋子
- **`Q` 命令**：结束当前游戏，输出最终棋盘状态

黑白棋的规则：双方轮流在棋盘上落子，落子时必须在水平、垂直或对角线方向上夹住至少一个对方棋子，被夹住的棋子会翻转为当前玩家的颜色。

## 解题思路

### 核心逻辑

1. **棋盘表示**：使用 $8 \times 8$ 的字符数组存储棋盘状态，`'B'` 表示黑棋，`'W'` 表示白棋，`'-'` 表示空格。

2. **方向数组**：使用预定义的 $8$ 个方向向量表示八个搜索方向：
   $$
   \begin{aligned}
   &(-1,0),\; (-1,1),\; (0,1),\; (1,1),\\
   &(1,0),\; (1,-1),\; (0,-1),\; (-1,-1)
   \end{aligned}
   $$

3. **合法落子检测**（`listMove` 函数）：
   - 遍历棋盘每个位置，若存在当前玩家的棋子，则沿 $8$ 个方向搜索
   - 遇到对方棋子继续，遇到空格或出界停止
   - 若在某方向上有连续的对方棋子且下一个位置是空格，则该空格为合法落子位置
   - 将合法位置用 `'*'` 临时标记，输出后恢复为 `'-'`

4. **落子与翻转**（`makeMove` 函数）：
   - 在指定位置放置当前玩家的棋子
   - 沿 $8$ 个方向搜索，统计连续对方棋子的数量
   - 若某方向连续对方棋子后遇到当前玩家的棋子，则将该方向上的所有对方棋子翻转

5. **无合法落子处理**：
   - 若当前玩家无合法落子，则自动切换为对方玩家
   - 切换后进行落子操作

6. **输出格式**：
   - 不同游戏之间输出一个空行
   - 移动后输出双方棋子数量，格式为 `Black - xx White - yy`

## 代码实现

```cpp
// Othello
// UVa ID: 220
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char board[8][8], player;          // board: 棋盘，player: 当前玩家
string command;                    // 存储命令
int direction[8][2] = {            // 8 个搜索方向
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, 
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

// 输出当前棋盘状态
void display() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            cout << board[i][j];
        cout << endl;
    }
}

// 列出当前玩家的所有合法落子位置
// print = true: 输出结果，print = false: 仅判断是否有合法落子
// 返回值: 是否有合法落子
bool listMove(bool print) {
    char another = player == 'B' ? 'W' : 'B';   // 对方棋子颜色
    // 遍历所有当前玩家棋子的位置，标记合法落子位置
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            if (board[x][y] == player) {
                for (int i = 0; i < 8; i++) {
                    int xx = x, yy = y;
                    int disks = 0;      // 连续对方棋子的数量
                    xx += direction[i][0];
                    yy += direction[i][1];
                    // 沿当前方向搜索，统计连续对方棋子
                    while (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) {
                        if (board[xx][yy] == another) disks++;
                        else break;
                        xx += direction[i][0];
                        yy += direction[i][1];
                    }

                    // 若存在对方棋子，且下一个位置是空格，则为合法落子
                    if (disks > 0 &&
                        (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) &&
                        board[xx][yy] == '-')
                        board[xx][yy] = '*';   // 临时标记合法位置
                }
            }

    // 收集并输出所有合法落子位置
    int legalMoves = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == '*') {
                if (print && legalMoves) cout << " ";
                if (print) cout << "(" << (i + 1) << "," << (j + 1) << ")";
                legalMoves++;
                board[i][j] = '-';   // 恢复为空格
            }
    // 输出结果信息
    if (print && legalMoves) cout << endl;
    else if (print) cout << "No legal move." << endl;
    return legalMoves > 0;
}

// 在指定位置落子，并翻转被夹住的棋子
void makeMove(int x, int y) {
    board[x][y] = player;           // 放置当前玩家棋子
    char another = player == 'B' ? 'W' : 'B';
    for (int i = 0; i < 8; i++) {
        int xx = x, yy = y;
        int disks = 0;
        xx += direction[i][0];
        yy += direction[i][1];
        // 统计当前方向上连续对方棋子的数量
        while (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) {
            if (board[xx][yy] == another) disks++;
            else break;
            xx += direction[i][0];
            yy += direction[i][1];
        }
        // 若该方向可翻转，则执行翻转操作
        if (disks > 0 &&
            (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) &&
            board[xx][yy] == player) {
            xx = x;
            yy = y;
            while (disks--) {
                xx += direction[i][0];
                yy += direction[i][1];
                board[xx][yy] = player;   // 翻转对方棋子
            }
        }
    }
}

// 根据命令执行相应操作
void play() {
    if (command == "L")                    // 列出合法落子
    {
        listMove(true);
    }
    else if (command.front() == 'M')       // 执行落子
    {
        // 若无合法落子，则切换玩家
        if (listMove(false) == false)
            player = player == 'B' ? 'W' : 'B';
        
        // 解析落子坐标（命令格式如 "M35" 表示第3行第5列）
        int x = command[1] - '0' - 1;
        int y = command[2] - '0' - 1;

        makeMove(x, y);                    // 执行落子并翻转

        // 统计黑白棋子数量
        int black = 0, white = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] == 'B')
                    black++;
                else if (board[i][j] == 'W')
                    white++;

        // 输出统计结果
        cout << "Black -" << setw(3) << right << black;
        cout << " White -" << setw(3) << right << white << endl;

        // 切换玩家（轮到对方落子）
        player = player == 'B' ? 'W' : 'B';
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    int games;
    bool first = true;
    cin >> games;
    while (games--) {
        // 读取棋盘初始状态
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> board[i][j];
        // 输出空行分隔不同游戏
        if (first) first = false;
        else cout << endl;
        // 读取当前玩家
        cin >> player;
        // 处理命令序列，直到遇到 'Q'
        while (cin >> command, command != "Q") play();
        // 输出最终棋盘状态
        display();
    }
    return 0;
}
```

## 总结

本题的核心在于准确实现黑白棋的规则模拟：

1. **合法落子检测**需要沿 $8$ 个方向搜索连续的对方棋子
2. **落子翻转**时需要在确认可翻转后，沿相同方向将棋子全部翻转
3. 注意处理**无合法落子时自动切换玩家**的规则

通过清晰的方向向量和规范的搜索逻辑，可以正确完成游戏模拟。
