[UVa 274 Cat and Mouse](https://blog.csdn.net/metaphysis/article/details/161333259)

## 题目分析

本题描述了一个由多个房间组成的房子，其中有一只猫和一只老鼠。猫和老鼠各自有一个“家”（起始房间）。猫只能在有猫门的房间之间单向移动，老鼠只能在有老鼠门的房间之间单向移动。猫门和老鼠门是分开的，彼此不能混用。

题目要求回答两个问题：

1. **是否存在猫和老鼠的行走路径，使得它们在某个房间相遇？** 即是否存在一个房间 $R$，使得猫可以从它的家出发到达 $R$，同时老鼠也可以从它的家出发到达 $R$。

2. **老鼠是否能走一条至少经过两个房间的回路（回到自己的家），且在整个过程中无论猫怎么走，老鼠都不会遇到猫？** 注意这里的关键是：老鼠的路径必须保证 **无论猫做什么**，都不会与老鼠相遇。这意味着老鼠必须完全避开所有猫能够到达的房间。

## 解题思路

### 问题一的解法

第一个问题相对直观。我们需要判断是否存在一个房间，使得猫和老鼠都能从各自的家到达该房间。

由于房间数量最大为 $100$，我们可以使用 **$\texttt{Floyd-Warshall}$ 算法** 来计算每对房间之间的可达性（或最短路径长度）。具体做法：

- 用邻接矩阵 $\texttt{cat}[i][j]$ 表示猫从房间 $i$ 到房间 $j$ 的最短路径长度。初始时，直接有猫门的房间之间设为 $1$，自己到自己的距离设为 $1$，其余设为一个大数（如 $10000$，表示不可达）。
- 用同样的方式处理老鼠的移动，得到 $\texttt{mouse}[i][j]$。

然后运行 $\texttt{Floyd-Warshall}$ 算法：

```cpp
for (int k = 0; k < roomNumber; k++)
    for (int i = 0; i < roomNumber; i++)
        for (int j = 0; j < roomNumber; j++) {
            if (cat[i][k] + cat[k][j] < cat[i][j]) cat[i][j] = cat[i][k] + cat[k][j];
            if (mouse[i][k] + mouse[k][j] < mouse[i][j]) mouse[i][j] = mouse[i][k] + mouse[k][j];
        }
```

算法结束后，遍历所有房间 $i$，如果 $\texttt{cat}[\textit{catHome}][i] < 10000$ 且 $\texttt{mouse}[\textit{mouseHome}][i] < 10000$，则说明猫和老鼠都能到达房间 $i$，可以相遇。输出 `'Y'`，否则输出 `'N'`。

### 问题二的解法

第二个问题更加复杂。老鼠要找到一条从自己家出发、经过至少两个房间、最终回到自己家的回路，并且在整个过程中 **无论猫怎么走**，老鼠都不会碰到猫。

这里的“无论猫怎么走”意味着：老鼠的整个路径上的每一个房间，都不能是猫 **能够到达** 的房间。因为如果某个房间是猫能够到达的，那么猫可以选择走到那个房间，从而遇到老鼠。

因此，我们需要首先确定所有猫能够到达的房间（从猫的家出发，通过猫门可达的房间）。这些房间对老鼠来说是 **禁区**。

首先标记了所有猫可达的房间：

```cpp
for (int i = 0; i < roomNumber; i++)
    if (cat[catHome][i] < 10000)
        for (int j = 0; j < roomNumber; j++)
            mouseSecond[j][i] = mouseSecond[i][j] = 0;
```

这里 $\texttt{mouseSecond}$ 矩阵用于表示在 **避开猫可达房间** 的条件下，老鼠的移动情况。初始时，$\texttt{mouseSecond}$ 被设置为 $0$。代码中有一个细节：当读取老鼠门时，代码将 $\texttt{mouseSecond}[start-1][end-1]$ 设置为 $-1$，表示存在一条老鼠门，并用 $-1$ 表示步数（相当于每条边的权值为 $-1$）。

为什么要用负权值？因为题目要求老鼠的回路 **至少经过两个房间**，意味着回路中至少包含两条边。如果我们用 $-1$ 表示每条边的长度，那么一条包含 $k$ 条边的回路的总长度为 $-k$。求最长的回路相当于求绝对值最大的负数（即最负的值）。

然后，我们需要在 **只使用不在猫可达区域的房间** 的条件下，计算老鼠的 $\texttt{Floyd-Warshall}$ 算法。但这里有一个重要的预处理：对于那些猫可达的房间，我们将其在 $\texttt{mouseSecond}$ 矩阵中对应的行和列全部清零（相当于从图中移除这些房间）。

接下来，在受限的图上再次运行 $\texttt{Floyd-Warshall}$ 算法：

```cpp
for (int k = 0; k < roomNumber; k++)
    for (int i = 0; i < roomNumber; i++)
        for (int j = 0; j < roomNumber; j++)
            if (mouseSecond[i][k] < 0 && mouseSecond[k][j] < 0 && mouseSecond[i][k] + mouseSecond[k][j] < mouseSecond[i][j])
                mouseSecond[i][j] = mouseSecond[i][k] + mouseSecond[k][j];
```

注意这里的条件：只有当 $\texttt{mouseSecond}[i][k] < 0$ 且 $\texttt{mouseSecond}[k][j] < 0$ 时，才进行松弛操作。因为负值表示存在有效的边或路径，而 $0$ 表示不可达（或被移除的房间）。

最后，检查 $\texttt{mouseSecond}[\textit{mouseHome}][\textit{mouseHome}]$ 的值。如果这个值 $\leq -2$，说明存在一条从老鼠家出发回到老鼠家的回路，且边数至少为 $2$（因为 $-2$ 表示 $2$ 条边，$-3$ 表示 $3$ 条边，以此类推）。代码中使用 `abs(mouseSecond[mouseHome][mouseHome])` 取绝对值，然后判断是否 $\geq 2$。

### 关于 $\texttt{Floyd-Warshall}$ 的应用说明

本题使用 $\texttt{Floyd-Warshall}$ 算法有两个目的：

1. **计算可达性**：对于第一个问题，我们关心的是是否存在一条路径，因此用 $1$ 表示有边，$\infty$ 表示无边，$\texttt{Floyd-Warshall}$ 可以求出任意两点之间的最短路径长度（非无穷即可达）。

2. **计算最长路径（回路）**：对于第二个问题，通过将边权设为 $-1$，将最长路径问题转化为最短路径问题（因为更负的值表示更长的路径）。$\texttt{Floyd-Warshall}$ 同样可以处理负权边（只要没有负权环，但这里负权环正是我们想要的，表示可以无限循环，不过题目只要求至少两个房间的回路，所以我们只需要检查是否存在长度为 $-2$ 或更负的回路）。

## 代码

```cpp
// Cat and Mouse
// UVa ID: 274
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cat[101][101], mouse[101][101], mouseSecond[101][101];
int roomNumber, catHome, mouseHome;

void findWalk() {
    // Floyd-Warshall 算法计算猫和老鼠的可达性（最短路径）
    for (int k = 0; k < roomNumber; k++)
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++) {
                if (cat[i][k] + cat[k][j] < cat[i][j]) cat[i][j] = cat[i][k] + cat[k][j];
                if (mouse[i][k] + mouse[k][j] < mouse[i][j]) mouse[i][j] = mouse[i][k] + mouse[k][j];
            }
            
    // 问题一：判断是否存在猫和老鼠都能到达的房间
    bool findRoom = false;
    for (int i = 0; i < roomNumber; i++)
        if (cat[catHome][i] < 10000 && mouse[mouseHome][i] < 10000) {
            findRoom = true;
            break;
        }
        
    cout << (findRoom ? "Y" : "N");
    
    // 问题二预处理：移除所有猫能够到达的房间（将其置为不可达）
    for (int i = 0; i < roomNumber; i++)
        if (cat[catHome][i] < 10000)
            for (int j = 0; j < roomNumber; j++)
                mouseSecond[j][i] = mouseSecond[i][j] = 0;
    
    // 在避开猫可达房间的图上，使用 Floyd-Warshall 计算最长路径（边权为 -1）
    for (int k = 0; k < roomNumber; k++)
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++)
                // 只有当中间路径都存在时（值为负）才进行松弛
                if (mouseSecond[i][k] < 0 && mouseSecond[k][j] < 0 && mouseSecond[i][k] + mouseSecond[k][j] < mouseSecond[i][j])
                    mouseSecond[i][j] = mouseSecond[i][k] + mouseSecond[k][j];
    
    // 检查是否存在从老鼠家出发回到老鼠家的回路（至少两条边）
    int longestWalk = abs(mouseSecond[mouseHome][mouseHome]);
    
    cout << (longestWalk >= 2 ? " Y" : " N") << endl;
}

int main() {
    int cases;
    cin >> cases;
    
    while (cases--) {
        cin >> roomNumber >> catHome >> mouseHome;
        catHome--;
        mouseHome--;
        
        // 初始化矩阵
        for (int i = 0; i < roomNumber; i++)
            for (int j = 0; j < roomNumber; j++) {
                cat[i][j] = 10000;      // 大数表示不可达
                mouse[i][j] = 10000;
                mouseSecond[i][j] = 0;  // 0 表示不可达（或已被移除）
            }
        
        // 自己到自己的距离设为 1
        cat[catHome][catHome] = 1;
        mouse[mouseHome][mouseHome] = 1;
            
        // 读取猫门信息
        int start, end;
        while (cin >> start >> end, start > 0 && end > 0)
            cat[start - 1][end - 1] = 1;
        
        // 读取老鼠门信息
        cin.ignore();
        string line;
        while (getline(cin, line), line.length() > 0) {
            sscanf(line.data(), "%d %d", &start, &end);
            mouse[start - 1][end - 1] = 1;
            mouseSecond[start - 1][end - 1] = -1;  // 用 -1 表示有一条边
        }
        
        findWalk();
        
        if (cases) cout << endl;
    }
    
    return 0;
}
```

## 总结

本题的核心在于：

1. 使用 $\texttt{Floyd-Warshall}$ 算法处理有向图的路径可达性问题。
2. 第二个问题需要识别“安全区域”——即猫无法到达的房间集合，老鼠只能在这个子图上移动。
3. 将最长路径问题转化为带负权的最短路径问题，利用 $\texttt{Floyd-Warshall}$ 算法求解回路。
