[UVa 360 Don't Get Hives From This One](https://blog.csdn.net/metaphysis/article/details/161611145)

## 题目描述

$\texttt{Billy Bee}$ 想利用蜂巢的一个废弃楼层作为“趣味迷宫”。他将出售门票赚大钱。下面的示例是“矩形”的，有 $11$ 行 $12$ 列。$\texttt{Billy}$ 的迷宫也将是矩形的，形状类似，但尺寸可能不同。单元格按所示模式用数字序列标识（从 $1$ 开始）。迷宫的特点是许多相邻单元格之间有开口。还有两个通向外部开口：入口和出口。

单元格的朝向如图所示（水平边和斜边，但没有垂直边）。迷宫的第二行从第一个房间的右下侧开始。

$\texttt{Billy}$ 已经布置好了迷宫，但他不太聪明，自己解不出来。他雇你来帮他找到一条穿过迷宫的路径。你决定使用著名的**右手法则**编写计算机程序来解决这种“矩形六边形迷宫”，并向 $\texttt{Billy Bee}$ 收取开发费用。

**右手法则**：当你进入一个平面迷宫时，将右手放在入口的墙上，然后向前走，手始终不离开墙壁，最终你会从出口门离开迷宫（如果出口不可达，你会从入口门离开）。

### 输入格式

输入文件包含零个或多个迷宫描述，紧随其后。

每个迷宫描述的第一行包含两个正整数 $r$ 和 $c$（$r \leq 30, c \leq 30$），用空格分隔，分别表示迷宫的行数和列数。或者，该行可能只包含两个零（空格分隔），表示没有更多迷宫需要读取和求解。

每个迷宫描述的第二行也包含两个正整数，用空格分隔，表示迷宫入口的房间号和墙壁编号。（每个房间的墙壁按顺时针方向编号，从顶墙 $=1$ 开始。）

第三行以相同方式标识迷宫出口的房间号和墙壁编号。入口和出口是不同的门。

其余行每行描述迷宫中的一个房间。每行包含一个房间号，后面跟着 $1$ 到 $6$ 个整数（每个在 $1$ 到 $6$ 范围内），用单个空格分隔。房间号后面的整数表示有开口的墙壁编号，可以是任意顺序，行的顺序也可以是任意的。数据集中的房间不会重复。未在数据集中列出的房间没有门。

迷宫描述的结束由一行只包含整数 `0` 表示。这行之后要么开始下一个迷宫描述，要么包含表示数据结束的两个零。

### 输出格式

首先，程序应列出搜索过程中遇到的房间序列，每行最多 $20$ 个房间（最后一行可能少于 $20$），同行值之间用单个空格分隔。注意，最后一个列出的房间要么是出口房间（如果找到解），要么是入口房间（否则）。

其次，在搜索路径最后一行下面一行输出 `SOLUTION FOUND` 或 `NO SOLUTION`，对应是否找到从入口到出口的路径。

### 样例输入

```
11 12
1 1
5 1
1 1 4
56 1
57 1 3 5 6
58 3 5
3 3
11 3 6
12 4
...
0
0 0
```

### 样例输出

```
1 13 7 14 26 31 19 25 37 49 43 49 37 25 19 31 26 14 7 13
1
NO SOLUTION
```

---

## 题目分析

### 问题的本质

这是一个**六边形网格迷宫**的模拟问题。六边形网格的每个单元格有 $6$ 个面（墙壁），编号 $1$ 到 $6$ 顺时针。每个门（开口）位于两个相邻单元格之间的墙上。使用**右手法则**模拟从入口到出口的路径。

### 六边形网格的几何

与正方形网格不同，六边形网格有奇偶行差异：
- 奇数行和偶数行的单元格偏移不同
- 每个六边形有 6 个邻居（分别为北、东北、东南、南、西南、西北）

### 右手法则

当从某个方向进入一个房间时，右手法则要求：
1. 将右手放在你进入时所经过的墙壁上
2. 顺时针旋转（保持手在墙上），找到第一个有门的墙壁
3. 通过那个门进入相邻房间
4. 重复直到到达出口或回到入口

在代码中，这表现为：从进入时的墙壁号开始，逆时针查找（因为进入方向与墙壁方向的关系），找到第一个有开口的墙壁。

### 坐标映射

由于房间编号是连续的（$1, 2, 3, \dots$），但六边形网格的几何结构复杂，需要使用一个映射表将逻辑房间号转换为网格坐标，以便确定相邻关系。
## 参考代码

```cpp
// Don't Get Hives From This One!
// UVa ID: 360
// Verdict: Accepted
// Submission Date: 2016-11-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 墙壁编号对应关系：进入墙壁的对面
int link[10] = {0, 4, 5, 6, 1, 2, 3};

int start, start_opening, dest, dest_opening;
int door[1000][10];           // 房间的墙壁开口信息
int adjacent[1000][10];       // 相邻房间编号
int to_cell[1000];            // 网格位置 → 房间号
int to_number[1000];          // 房间号 → 网格位置
int enabled[1000];            // 该网格位置是否存在
bool finished;                // 是否完成搜索
vector<int> sequences;        // 路径序列

// 右手法则 DFS
void dfs(int room, int wall) {
    if (finished) return;

    sequences.push_back(room);

    // 检查是否到达出口
    int next_wall = wall;
    for (int k = 1; k <= 6; k++) {
        next_wall--;
        if (next_wall <= 0) next_wall += 6;
        if ((room == to_number[start] && next_wall == start_opening) ||
            (room == to_number[dest] && next_wall == dest_opening)) {
            finished = true;
            return;
        }
        if (door[room][next_wall]) break;
    }

    // 如果没有出口或邻居不存在，结束
    if (!adjacent[room][next_wall] || !enabled[adjacent[room][next_wall]]) {
        finished = true;
        return;
    }
    
    // 进入相邻房间
    dfs(adjacent[room][next_wall], link[next_wall]);
}

// 将网格位置映射到房间号
void map_cell_to_number(int r, int c) {
    memset(to_cell, 0, sizeof(to_cell));
    memset(to_number, 0, sizeof(to_number));

    int offset = c / 2 + c % 2, base = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (j % 2 == 1) {
                to_cell[(i - 1) * 30 + j] = base + (j + 1) / 2;
                to_number[base + (j + 1) / 2] = (i - 1) * 30 + j;
            } else {
                to_cell[(i - 1) * 30 + j] = base + j / 2 + offset;
                to_number[base + j / 2 + offset] = (i - 1) * 30 + j;
            }
        }
        base += c;
    }

    memset(enabled, 0, sizeof(enabled));
    int cells = 0;
    for (int i = 1; i <= r; i++)
        cells += (i % 2 == 1) ? ((c + 1) / 2) : (c / 2);
    for (int i = 1; i <= cells; i++)
        enabled[to_number[i]] = 1;
}

// 初始化六边形网格的相邻关系
void initialize() {
    int offset[2][6] = {{-30, 1, 31, 30, 29, -1}, {-30, -29, 1, 30, -1, -31}};

    memset(adjacent, 0, sizeof(adjacent));
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 30; j++) {
            int number = (i - 1) * 30 + j;
            for (int k = 1; k <= 6; k++)
                adjacent[number][k] = number + offset[j % 2][k - 1];
            // 边界处理
            if (i == 1) {
                adjacent[number][1] = 0;
                if (j % 2 == 1) adjacent[number][2] = adjacent[number][6] = 0;
            }
            if (i == 15) {
                adjacent[number][4] = 0;
                if (j % 2 == 0) adjacent[number][3] = adjacent[number][5] = 0;
            }
            if (j == 1) adjacent[number][5] = adjacent[number][6] = 0;
            if (j == 30) adjacent[number][2] = adjacent[number][3] = 0;
        }
}

int main() {
    initialize();

    int r, c;
    string line;

    while (cin >> r >> c, r > 0) {
        // 映射房间号到网格位置
        map_cell_to_number(r, c);
        memset(door, 0, sizeof(door));
        
        // 读取入口和出口
        cin >> start >> start_opening >> dest >> dest_opening;

        // 读取房间门信息
        int room, wall;
        while (cin >> room, room > 0) {
            getline(cin, line);
            istringstream iss(line);
            while (iss >> wall) 
                door[to_number[room]][wall] = 1;
        }
        
        // 右手法则 DFS
        sequences.clear();
        finished = false;
        dfs(to_number[start], start_opening);

        // 输出路径
        for (int i = 0; i < sequences.size(); i++) {
            cout << to_cell[sequences[i]];
            if ((i + 1) == sequences.size() || (i + 1) % 20 == 0) cout << '\n';
            else cout << ' ';
        }

        // 输出结果
        if (sequences.back() == to_number[dest]) cout << "SOLUTION FOUND\n";
        else cout << "NO SOLUTION\n";
    }
    return 0;
}
```
